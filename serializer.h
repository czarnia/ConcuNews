#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "socket.h"

#define SOCK_SEND(s, T, x) socket_send((s), (char *)&(x), (size_t) sizeof(T))

#define SOCK_RECV(s, T, x) socket_receive((s), (char *)&(x), (size_t) sizeof(T))

typedef enum _msg_type {
	MSG_STORE = 0,
	MSG_RETRIEVE,
	MSG_RESPONSE,
	MSG_ERROR
} msg_type;

typedef enum _role {
	ROLE_USER = 0,
	ROLE_ADMIN
} role_t;

typedef enum _service {
	SVC_CURRENCY = 0,
	SVC_TEMPERATURE
} service_t;

typedef struct _service_msg {
	msg_type type;
	char city_name[66];
	char city_value[34];
} service_msg_t;


typedef struct _server_msg {
	msg_type type;
	role_t role;
	service_t service;
	char city_name[66];
	char city_value[34];
} server_msg_t;

struct msg {
	int role;
	int service;
};


#endif
