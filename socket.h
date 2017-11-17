#ifndef _SOCKET_H
#define _SOCKET_H

#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

typedef enum _socket_type {
	SOCK_ACTIVE = 0,
	SOCK_PASSIVE
} socket_type;

typedef struct socket socket_t;

/*
 * Creates a new socket of the specified type
 */
socket_t* socket_create(socket_type type);




//Destruye un socket_t*
void socket_destroy(socket_t* self);

//Habilita al socket para escuchar, devuelve <0 en caso de error
int socket_listen(socket_t* self, int backlog);

//Hace un bind del socket, devuelve <0 en caso de error
int socket_bind(socket_t* self, char* hostname, char* port);

//Hace un accept del socket, devuelve <0 en caso de error
socket_t* socket_accept(socket_t* self);

//Hace un conect del socket, devuelve <0 en caso de error
int socket_conect(socket_t* self, char* hostname, char* port);

//Hace un receive del socket, determinando cuanta informacion se piensa recibir
//, devuelve <0 en caso de error
int socket_receive(socket_t* self, char* buffer, size_t tamanio);

//Hace un send del socket, determinando cuanta informacion se piensa enviar,
//devuelve <0 en caso de error
int socket_send(socket_t* self, const char* buffer, size_t tamanio);


#endif // _SOCKET_H
