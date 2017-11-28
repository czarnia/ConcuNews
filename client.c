#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include "socket.h"
#include "serializer.h"
#include <string.h>

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "16007"

#define PASSWORD "iamadmin"

#define CMD_STORE "ST"
#define CMD_RETRIEVE "RT"
#define SVC_CURRENCY_STR "cur"
#define SVC_TEMPERATURE_STR "tmp"

static const server_msg_t EMPTY_MSG = { 0 };

void print_msg(server_msg_t* msg) {
	printf("\tCity: %s, Value: %s\n", msg->city_name, msg->city_value);
	printf("\tService: %d, Role: %d\n", msg->service, msg->role);
}

service_t choose_service(char* service_str) {
	if (strcmp(service_str, SVC_TEMPERATURE_STR) == 0) {
		return SVC_TEMPERATURE;
	} else if (strcmp(service_str, SVC_CURRENCY_STR) == 0) {
		return SVC_CURRENCY;
	}
	return SVC_INVALID;
}

server_msg_t* get_msg(int argc, char* argv[]) {
	if (argc <= 3) {
		printf("Not enough arguments\n");
		return NULL;
	}	       

	server_msg_t* msg = malloc(sizeof(server_msg_t));
	*msg = EMPTY_MSG;
	strcpy(msg->city_name, argv[3]);

	if ((msg->service = choose_service(argv[2])) == SVC_INVALID) {
		free(msg);
		printf("Invalid service\n");
		return NULL;
	}
	if (strcmp(argv[1], CMD_STORE) == 0) {
		if (argc != 5) {
			printf("Invalid number of arguments\n");
			return NULL;
		}	

		printf("You need admin access to store values, please type your password:\n");
		char buffer[60];
		buffer[0] = '\0';
		size_t n = 59;
		fscanf(stdin, "%s", buffer);
		printf("Password is: %s\n", buffer);
		if ((strcmp(buffer, PASSWORD) != 0)) {
			free(msg);
			printf("Invalid password\n");
			return NULL;
		}
		
		msg->type = MSG_STORE;
		msg->role = ROLE_ADMIN;
		strcpy(msg->city_value, argv[4]);

	} else if (strcmp(argv[1], CMD_RETRIEVE) == 0) {
		msg->type = MSG_RETRIEVE;
		msg->role = ROLE_USER;
	} else {
		free(msg);
		printf("Invalid operation\n");
		return NULL;
	}
	return msg;
}


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

	//server_msg_t msg = { MSG_RETRIEVE, ROLE_USER, SVC_TEMPERATURE, "BuenosAires", "" };
	server_msg_t* msg = get_msg(argc, argv);
	if (!msg) {
		socket_destroy(s);
		return -1;
	}

	err = SOCK_SEND(s, server_msg_t, *msg);
	if (err < 0) {
		printf("Error sending message\n");
		socket_destroy(s);
		return -1;
	}

	err = SOCK_RECV(s, server_msg_t, *msg);
	if (err < 0) {
		printf("Error receiving message\n");
		socket_destroy(s);
		return -1;
	}

	printf("Destroying socket\n");
	socket_destroy(s);

	assert(msg->type == MSG_RESPONSE);
	print_msg(msg);
	free(msg);

	return 0;
}
