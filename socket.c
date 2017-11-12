#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>

#include "socket.h"
#include <stdlib.h>

struct socket{
  int skt;
  struct addrinfo* info;
};


struct addrinfo* iniciar_addrinfo(char* ip, char* puerto){
  struct addrinfo hints;
  struct addrinfo* server;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  getaddrinfo(ip, puerto, &hints, &server);

  return server;
}


void socket_crear(socket_t* self, char* ip, char* puerto){
  self->addrinfo = iniciar_addrinfo(ip, puerto);
  self->skt = socket(self->addrinfo->ai_family, self->addrinfo->ai_socktype, self->addrinfo->ai_protocol);
}


void socket_destroy(socket_t* self){
  close(self->skt);
}


int socket_shutdown(socket_t* self, int como){
  return shutdown (self->skt, como);
}


int socket_listen(socket_t* self, int conexiones){
  return listen(self->skt, conexiones);
}


int socket_bind(socket_t* self){
  return bind(self->skt, self->addrinfo->ai_addr, self->addrinfo->ai_addrlen);
}


int socket_accept(socket_t* self, struct sockaddr dir_cliente, socket_t* skt){
  socklen_t tam_addr = sizeof(dir_cliente);
  return skt->skt = accept(self->skt, &dir_cliente, &tam_addr);
}

int socket_conect(socket_t* self){
  return connect(self->skt, self->addrinfo->ai_addr, self->addrinfo->ai_addrlen);
}


int socket_receive(socket_t* self, char* buffer, size_t tamanio){
  size_t tam_actual = 0; //el tamaño total de lo que ya recibí.
  int tam_rcv = 0; //el tamaño de lo que recibo en cada ciclo.

  while (tam_actual < tamanio){
    int dif_tam = tamanio-tam_actual;
    tam_rcv = recv(self->skt, &buffer[tam_actual], dif_tam, MSG_NOSIGNAL);
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
    tam_send = send(self->skt, &buffer[tam_actual], dif_tam, MSG_NOSIGNAL);
    if (tam_send <= 0){
      return -1;
    }
    tam_actual += tam_send;
  }

  return tam_actual;
}
