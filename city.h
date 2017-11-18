#ifndef _CITY_H
#define _CITY_H

#include <stddef.h>
#include <stdbool.h>

typedef struct city{
    char* name;
    float value;
} city_t;

typedef struct city_vector{
    city_t* vec;
    size_t size;
    size_t quantity;
} city_vector_t;


//It creates a city, the city has its name and a value that could be the currency
//conversion to an argentine peso or its temperature.
city_t city_create(char* name, float value);
//Getter for the city name.
char* city_name(city_t city);
//Getter for the value of the city (currency or temperature).
float city_value(city_t city);


//It creates a vector of cities.
city_vector_t* city_vector_create();
//Getter for the size of the city vector.
size_t city_vector_size(city_vector_t* v);
//It returns the city that it is stores in the posicion i of the vector.
city_t city_vector_get(city_vector_t* v, size_t i);
//It adds a new city to the vector in the last available position of it.
bool city_vector_add(city_vector_t* v, city_t city);
//It destroys the city vector.
void city_vector_destroy(city_vector_t* v);


#endif // _CITY_H
