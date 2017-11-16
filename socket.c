#define _POSIX_C_SOURCE 200112L

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>	// htons, htonl, etc
#include <string.h>	// memset
#include <stdlib.h>

#include <assert.h>

#include "socket.h"

struct socket {
	int sock;
	socket_type type;
	struct addrinfo* ai;
	struct addrinfo* peer_ai;
};


/*
 * Initializes an struct addrinfo via getaddrinfo().
 * ai_family is set to AF_INET
 * ai_socktype is set to SOCK_STREAM
 * ai_protocol is set to 0
 * ai_flags is set to prevent name resolution that is not numeric
 *	(i.e. resolve "127.0.0.1" but not "google.com")
 */
int init_addrinfo(struct addrinfo** ai_store, char* hostname, char* service) {
	assert(ai_store != NULL);

	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICHOST || AI_NUMERICSERV;

	int err = getaddrinfo(hostname, service, &hints, ai_store);
	if (err)
		ai_store = NULL;

	return err;
}

/*
 * Creates a new socket of the specified type:
 *   - SOCK_PASSIVE for servers
 *   - SOCK_ACTIVE for clients
 */
socket_t* socket_create(socket_type type) {
	socket_t* sock = malloc(sizeof(socket_t));
	sock->ai = NULL;
	sock->peer_ai = NULL;
	sock->type = type;
	sock->sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock->sock < 0) {
		free(sock);
		sock = NULL;
	}
	return sock;
}

/*
 * Closes and destroys a socket, freeing any addrinfo
 */
void socket_destroy(socket_t* self) {
	if (self->ai)
		freeaddrinfo(self->ai);
	if (self->peer_ai)
		freeaddrinfo(self->ai);
	close(self->sock);
	free(self);
}

/*
 * Attemps to bind the socket to a specific hostname and service.
 * Both are specified in 'presentation' format and resolved via init_addrinfo().
 * Fail if already binded.
 */
int socket_bind(socket_t* self, char* hostname, char* port){
	assert(self->ai == NULL);
	int err = init_addrinfo(&self->ai, hostname, port);
	if (err)
		return err;

	// TODO: assert addrinfo is correct type and family
	err = bind(self->sock, self->ai->ai_addr, self->ai->ai_addrlen);
	if (err)
		freeaddrinfo(self->ai);

	return err;
}



int socket_listen(socket_t* self, int conexiones){
	assert(self->type = SOCK_PASSIVE);
	return listen(self->sock, conexiones);
}


int socket_accept(socket_t* self, struct sockaddr* dir_cliente, socket_t* sock){
	assert(self->type = SOCK_PASSIVE);
	socklen_t tam_addr = sizeof(dir_cliente);
	return sock->sock = accept(self->sock, dir_cliente, &tam_addr);
}

int socket_conect(socket_t* self){
	assert(self->type = SOCK_ACTIVE);
	return connect(self->sock, self->ai->ai_addr, self->ai->ai_addrlen);
}


int socket_receive(socket_t* self, char* buffer, size_t tamanio){
	size_t tam_actual = 0; //el tamaño total de lo que ya recibí.
	int tam_rcv = 0; //el tamaño de lo que recibo en cada ciclo.

	while (tam_actual < tamanio){
		int dif_tam = tamanio-tam_actual;
		tam_rcv = recv(self->sock, &buffer[tam_actual], dif_tam, MSG_NOSIGNAL);
		if (tam_rcv <= 0){
			return -1;
		}
		tam_actual += tam_rcv;
	}

	return tam_actual;
}


int socket_send(socket_t* self, const char* buffer, size_t tamanio){
	size_t tam_actual = 0; //el tamaño total de lo que ya envié.
	int tam_send = 0; //el tamaño de lo que envio en cada ciclo.

	while (tam_actual < tamanio){
		int dif_tam = tamanio-tam_actual;
		tam_send = send(self->sock, &buffer[tam_actual], dif_tam, MSG_NOSIGNAL);
		if (tam_send <= 0){
			return -1;
		}
		tam_actual += tam_send;
	}

	return tam_actual;
}

int socket_shutdown(socket_t* self, int como){
	return shutdown (self->sock, como);
}
