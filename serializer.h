#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "socket.h"

#define SOCK_SEND(s, T, x) socket_send((s), (char *)&(x), (size_t) sizeof(T))

#define SOCK_RECV(s, T, x) socket_receive((s), (char *)&(x), (size_t) sizeof(T))

#endif
