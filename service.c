#include <stdio.h>
#include <string.h>

#include "service.h"
#include "serializer.h"
#include "parser.h"
#include "city.h"

void service_handlder(socket_t* s, char* path) {
	service_msg_t msg;
	int err	= SOCK_RECV(s, service_msg_t, msg);
	if (err < 0) {
		printf("Service handler recv error\n");
		return;
	}

	printf("Service received a message: City: %s, Currency: %s\n", msg.city_name, msg.city_value);
	city_vector_t* cities = get_cities(path);
	printf("Service read cities\n");

	if (msg.type == MSG_RETRIEVE) {
		printf("Service says: It's a retrieve!\n");
		int index = city_vector_get_by_name(cities, msg.city_name);
		printf("Service: index is: %d\n", index);
		if (index >= 0) {
			city_t city = city_vector_get(cities, index);
			strcpy(msg.city_value, city.value);
			msg.type = MSG_RESPONSE;
			printf("City: %s, Currency: %s\n", msg.city_name, msg.city_value);
			err = SOCK_SEND(s, service_msg_t, msg);
		} else {
			msg.type = MSG_ERROR;
			err = SOCK_SEND(s, service_msg_t, msg);
		}
		city_vector_destroy(cities);
	} else if (msg.type == MSG_STORE) {
		printf("Service says: It's a store!\n");
		city_t city = city_create(msg.city_name, msg.city_value);
		if (!city_vector_add(cities, city)) {
			msg.type = MSG_ERROR;
			err = SOCK_SEND(s, service_msg_t, msg);
			return;
		}

		store_cities(cities, path);

		msg.type = MSG_RESPONSE;
		err = SOCK_SEND(s, service_msg_t, msg);
	} else {
		msg.type = MSG_ERROR;
		err = SOCK_SEND(s, service_msg_t, msg);
		printf("Service handler type error\n");
		city_vector_destroy(cities);
	}
}


