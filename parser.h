#ifndef _PARSER_H
#define _PARSER_H

#include <stddef.h>

#include "city.h"

//Given the name of a file that stores the data of certains cities in the format:
// NAME CURRENCY_CONVERSION_TO_ARGENTINE_PESO/TEMPERATURE
//it reads it and returns all the city_t that it contains in a city_vector_t* (dinamically allocated).
city_vector_t* get_cities(char* cities_file);

//Given an array of city_t*, it stores the data of the cities in a file of name
//"cities_file", if the name is taken, the file is rewritten.
//It also deletes the city_vector_t* taken as a parameter (it should be the one
//created in get_cities).
void store_cities(city_vector_t* cities, char* cities_file);

#endif // _PARSER_H
