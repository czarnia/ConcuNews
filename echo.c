#define _POSIX_C_SOURCE 200112L

#include "socket.h"
#include "serializer.h"
#include "server.h"
#include <sys/types.h>

#include <stdio.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "16000"

void new_client(socket_t* s) {
	char c = 'a';
	int err = 0;
	while (c != 'q') {
		err = SOCK_RECV(s, char, c);
		if (err < 0) return;

		err = SOCK_SEND(s, char, c);
		if (err < 0) return;
	}
}

int main(int argc, char* argv[]) {
	run_server(SERVER_IP, SERVER_PORT, new_client, SERVER_CONCURRENT);
	return 0;
}
