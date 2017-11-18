#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "parser.h"

#define END_LINE '\n'
#define END_STRING '\0'
#define NUM_VALUES 2
#define MAX_STRING_SIZE 66
#define MAX_SIZE 100 //We are assuming the city with the longest name is Llanfair­pwllgwyngyll­gogery­chwyrn­drobwll­llan­tysilio­gogo­goch,
//having 33 digits for the temperature or for the value of its currency and 1 for the separator.

#define INI_SIZE 5;

//----------------->Aux Functions<-----------------//

void read_line(FILE* f, char* line){
    char c = getc(f);
    for (int i = 0; i < MAX_SIZE && c != END_LINE; i++){
        if (c == EOF){
            line[i] = END_STRING;
            return;
        }
        line[i] = c;
        c = getc(f);
    }
    line[MAX_SIZE] = END_STRING;
}

void split_values(char* line, char* separator, char** values){
    for (int i = 0; i < NUM_VALUES; i++){
        values[i] = strsep(&line, separator);
    }
}

//------------------------------------------------------------------------------//

city_vector_t* get_cities(char* cities_file){
    city_vector_t* cities = city_vector_create();
    if (!cities){
        return NULL;
    }

    FILE* f = fopen(cities_file, "r");
    if (!f){
        return NULL;
    }

    int i = 0;
    char line[MAX_SIZE];
    read_line(f, line);

    while(line){
        char* processed_line[NUM_VALUES];
        split_values(line, " ", processed_line);
        char* city_name = processed_line[0];
        float value = atof(processed_line[1]);

        city_t city = city_create(city_name, value);
        if (!city_vector_add(cities, city)){
            city_vector_destroy(cities);
            fclose(f);
            return NULL;
        }
        read_line(f, line);
        i++;
    }
    return cities;
}

void store_cities(city_vector_t* cities, char* cities_file){
    FILE* f = fopen(cities_file, "w+");

    if (!f){
        return;
    }

    for (int i = 0; i < city_vector_size(cities); i++){
        char line[MAX_SIZE];
        city_t city = city_vector_get(cities, i);
        sprintf(line, "%s %f", city_name(city), city_value(city));
        fwrite(line, sizeof(char), strlen(line), f);
    }

    city_vector_destroy(cities);
}
