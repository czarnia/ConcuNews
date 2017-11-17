#define _POSIX_C_SOURCE 200112L

#include "socket.h"
#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>



#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "16000"



void new_client(socket_t* s) {
	char c = 'a';
	int err = 0;
	while (c != 'q') {
		err = socket_receive(s, &c, 1);
		printf("%c - %d\n", c, err);
		if (err < 0) return;

		err = socket_send(s, &c, 1);
		printf("%c - %d\n", c, err);
		if (err < 0) return;
	}
}




int main(int argc, char* argv[]) {
	getc(stdin);
	printf("Creating socket\n");
	socket_t* s = socket_create(SOCK_PASSIVE);

	printf("Binding socket\n");
	int err = socket_bind(s, SERVER_IP, SERVER_PORT);
	if (err < 0) {
		printf("Binding failed: %d\n", err);
		socket_destroy(s);
		return -1;
	}

	printf("Setting socket as passive\n");
	err = socket_listen(s, 0);
	if (err < 0) {
		printf("Listen failed: %d\n", err);
		socket_destroy(s);
		return -1;
	}

	printf("Listening on socket %s:%s\n", SERVER_IP, SERVER_PORT);
	socket_t* s2 = socket_accept(s);
	if (!s2) {
		printf("Accept failed\n");
	} else {
		printf("Accept successful!\n");
		getc(stdin);
		new_client(s2);
		socket_destroy(s2);
	}

	socket_destroy(s);
	return 0;
}
