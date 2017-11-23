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

typedef struct _service_msg {
	msg_type type;
	char city_name[66];
	char city_value[34];
} service_msg_t;

struct msg {
	int role;
	int service;
};


#endif
