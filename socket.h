#ifndef _SOCKET_H
#define _SOCKET_H

#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


typedef struct socket socket_t;

//Crea un socket_t*
void socket_crear(socket_t* self, int dominio, int tipo, int protocolo);

//Destruye un socket_t*
void socket_destroy(socket_t* self);

//Le hace un shutdown a un socket_t*, devuelve <0 en caso de error
int socket_shutdown(socket_t* self, int como);

//Habilita al socket para escuchar, devuelve <0 en caso de error
int socket_listen(socket_t* self, int conexiones);

//Hace un bind del socket, devuelve <0 en caso de error
int socket_bind(socket_t* self, struct sockaddr* direccion, int tamanio);

//Hace un accept del socket, devuelve <0 en caso de error
int socket_accept(socket_t* self, struct sockaddr* dir_cliente, socket_t* skt);

//Hace un conect del socket, devuelve <0 en caso de error
int socket_conect(socket_t* self, struct sockaddr* dir_server, int tamanio);

//Hace un receive del socket, determinando cuanta informacion se piensa recibir
//, devuelve <0 en caso de error
int socket_receive(socket_t* self, char* buffer, size_t tamanio);

//Hace un send del socket, determinando cuanta informacion se piensa enviar,
//devuelve <0 en caso de error
int socket_send(socket_t* self, char* buffer, size_t tamanio);



#endif // _SOCKET_H
