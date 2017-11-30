#include "city.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INI_SIZE 5

//------------------->Functions City<-------------------//

city_t city_create(char* name, char* value){
    city_t city;
    strcpy(city.name, name);
    strcpy(city.value, value);
    return city;
}

char* city_name(city_t city){
    static char str_aux[66];
    strcpy(str_aux, city.name);
    return str_aux;
}

char* city_value(city_t city){
    static char str_aux[100];
    strcpy(str_aux, city.value);
    return str_aux;
}

//------------------->Functions City vector<-------------------//

city_vector_t* city_vector_create(){
    city_vector_t* vector = malloc(sizeof(city_vector_t));
    if (!vector){
        return NULL;
    }
    vector->vec = malloc(INI_SIZE * sizeof(city_t));
    if (!vector->vec){
        return NULL;
    }
    vector->size = INI_SIZE;
    vector->quantity = 0;
    return vector;
}

size_t city_vector_quantity(city_vector_t* v){
    return v->quantity;
}

city_t city_vector_get(city_vector_t* v, size_t i){
    return v->vec[i];
}

int city_vector_get_by_name(city_vector_t* v, char* city_name) {
	printf("Getting city by name!\n");
	printf("%zu\n", v->quantity);
	for (int i = 0; i < v->quantity; i++) {
		printf("%s - %s\n", city_name, v->vec[i].name);
		if (strcmp(city_name, v->vec[i].name) == 0) {
			return i;
		}
	}
	return -1;
}

bool city_vector_add(city_vector_t* v, city_t city){
	int index = city_vector_get_by_name(v, city.name);
	if (index >= 0) {
		strcpy(v->vec[index].value, city.value);
		return true;
	}


	if (v->size == v->quantity){
		city_t* new_vec = realloc(v->vec, sizeof(city_t)*v->quantity*2);
		if (!new_vec){
			return false;
		}
		v->vec = new_vec;
	}
	v->vec[v->quantity] = city;
	v->quantity++;
	return true;
}

void city_vector_destroy(city_vector_t* v){
    free(v->vec);
    free(v);
}
