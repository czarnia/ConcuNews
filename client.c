#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include "socket.h"
#include "serializer.h"

#include <stdio.h>
#include <assert.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "16001"




int main(int argc, char* argv[]) {
	printf("Creating socket\n");
	socket_t* s = socket_create(SOCK_ACTIVE);
	if (!s) {
		printf("Error creating socket\n");
		return -1;
	}

	printf("Connecting socket\n");
	int err = socket_conect(s, SERVER_IP, SERVER_PORT);
	if (err < 0) {
		printf("Error connecting\n");
		socket_destroy(s);
		return -1;
	}

	service_msg_t msg = { MSG_RETRIEVE, "BuenosAires", "" };

	err = SOCK_SEND(s, service_msg_t, msg);
	if (err < 0) {
		printf("Error sending message\n");
		socket_destroy(s);
		return -1;
	}

	err = SOCK_RECV(s, service_msg_t, msg);
	if (err < 0) {
		printf("Error receiving message\n");
		socket_destroy(s);
		return -1;
	}

	printf("Destroying socket\n");
	socket_destroy(s);

	assert(msg.type == MSG_RESPONSE);
	printf("City: %s, Currency: %s\n", msg.city_name, msg.city_value);

	return 0;
}
