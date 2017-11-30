#include "service.h"
#include "server.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "16002"

void temperature_service_handler(socket_t* s) {
	service_handlder(s, "temperature.csv");
}

int main (int argc, char* argv[]) {
	run_server(SERVER_IP, SERVER_PORT, temperature_service_handler, SERVER_ITERATIVE);
	return 0;
}
