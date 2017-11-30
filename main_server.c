#define _POSIX_C_SOURCE 200112L

#include "socket.h"
#include "serializer.h"
#include "server.h"
#include "string.h"
#include <sys/types.h>

#include <stdio.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "16007"

#define CURRENCY_PORT "16003"
#define TEMPERATURE_PORT "16002"

static server_msg_t ERROR_MSG = { 0 };

void new_client(socket_t* s) {
	ERROR_MSG.type = MSG_ERROR;
	server_msg_t msg;
	int err	= SOCK_RECV(s, server_msg_t, msg);
	if (err < 0) {
		printf("Server handler recv error\n");
		SOCK_SEND(s, server_msg_t, ERROR_MSG);
		return;
	}

	if ((msg.type == MSG_STORE) && (msg.role != ROLE_ADMIN)) {
		printf("Kb gato\n");
		SOCK_SEND(s, server_msg_t, ERROR_MSG);
		return;
	}

	socket_t* svc_sock = socket_create(SOCK_ACTIVE);
	if (!svc_sock) {
		printf("Error creating socket\n");
		SOCK_SEND(s, server_msg_t, ERROR_MSG);
		return;
	}

	if (msg.service == SVC_CURRENCY) {
		err = socket_conect(svc_sock, SERVER_IP, CURRENCY_PORT);
	} else if (msg.service == SVC_TEMPERATURE) {
		err = socket_conect(svc_sock, SERVER_IP, TEMPERATURE_PORT);
	} else {
		socket_destroy(svc_sock);
		printf("Error service not found\n");
		SOCK_SEND(s, server_msg_t, ERROR_MSG);
		return;
	}
	printf("Connecting socket\n");
	if (err < 0) {
		printf("Error connecting\n");
		socket_destroy(svc_sock);
		SOCK_SEND(s, server_msg_t, ERROR_MSG);
		return;
	}

	service_msg_t msg_svc = { 0 };
	strcpy(msg_svc.city_name, msg.city_name);
	strcpy(msg_svc.city_value, msg.city_value);
	msg_svc.type = msg.type;
	err = SOCK_SEND(svc_sock, service_msg_t, msg_svc);
	if (err < 0) {
		printf("Error sending request\n");
		socket_destroy(svc_sock);
		SOCK_SEND(s, server_msg_t, ERROR_MSG);
		return;
	}

	err = SOCK_RECV(svc_sock, service_msg_t, msg_svc);
	if (err < 0) {
		printf("Error receiving request\n");
		socket_destroy(svc_sock);
		SOCK_SEND(s, server_msg_t, ERROR_MSG);
		return;
	}

	socket_destroy(svc_sock);

	strcpy(msg.city_value, msg_svc.city_value);
	msg.type = msg_svc.type;
	err = SOCK_SEND(s, server_msg_t, msg);
	if (err < 0) {
		printf("Error sending response\n");
		return;
	}
	return;
}

int main(int argc, char* argv[]) {
	run_server(SERVER_IP, SERVER_PORT, new_client, SERVER_CONCURRENT);
	return 0;
}
