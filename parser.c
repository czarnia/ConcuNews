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
    int i = 0;
    for (i; i < MAX_SIZE && c != END_LINE; i++){
        if (c == EOF){
            line[i] = END_STRING;
            return;
        }
        line[i] = c;
        c = getc(f);
    }
    line[i] = END_STRING;
}

void split_values(char* line, char separator, char** values){
    char str[MAX_STRING_SIZE];
    int j = 0;
    int size_str = 0;
    for (int i = 0; i < strlen(line); i++){
        if (line[i] == separator){
            str[size_str] = END_STRING;
            char str_aux[size_str];
            strcpy(str_aux, str);
            strcpy(values[j], str_aux);
            size_str = 0;
            j++;
        }else{
            str[size_str] = line[i];
            size_str++;
        }
    }
    str[size_str] = END_STRING;
    char str_aux[size_str];
    strcpy(str_aux, str);
    strcpy(values[j], str_aux);
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
    printf("%s\n", line);

    while(line){
        char* processed_line[NUM_VALUES];
        split_values(line, ' ', processed_line);
        char city_name[MAX_STRING_SIZE];
        char value_str[MAX_STRING_SIZE];
        strcpy(city_name, processed_line[0]);
        strcpy(value_str, processed_line[1]);

        float value = atoi(value_str);

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

    //city_vector_destroy(cities);
}
