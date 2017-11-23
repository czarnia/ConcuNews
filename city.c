#include "city.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INI_SIZE 5

//------------------->Functions City<-------------------//

city_t city_create(char* name, float value){
    city_t city;
    strcpy(city.name, name);
    city.value = value;
    return city;
}

char* city_name(city_t city){
    static char str_aux[66];
    strcpy(str_aux, city.name);
    return str_aux;
}

float city_value(city_t city){
    return city.value;
}

//------------------->Functions City vector<-------------------//

city_vector_t* city_vector_create(){
    city_vector_t* vector = calloc(1, sizeof(city_vector_t));
    if (!vector){
        return NULL;
    }
    vector->vec = calloc(INI_SIZE, sizeof(city_t));
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

bool city_vector_add(city_vector_t* v, city_t city){
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
