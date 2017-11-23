#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "parser.h"

#define END_LINE '\n'
#define END_STRING '\0'
#define NUM_VALUES 2
#define MAX_STRING_SIZE 66
#define MAX_SIZE 100 //We are assuming the city with the longest name is Llanfair­pwllgwyngyll­gogery­chwyrn­drobwll­llan­tysilio­gogo­goch,
//having 33 digits for the temperature or for the value of its currency and 1 for the separator.

#define INI_SIZE 5;

//----------------->Aux Functions<-----------------//

void read_line(int f, char* line){
    char c = 0;
    read(f, &c, 1);
    int i = 0;
    for (i; i < MAX_SIZE && c != END_LINE; i++){
        if (c == EOF){
            line[i] = END_STRING;
            return;
        }
        line[i] = c;
	read(f, &c, 1);
    }
    line[i] = END_STRING;
}

void split_values(char* line, char separator, char* city_name, char* city_value){
    char str[MAX_STRING_SIZE];
    int j = 0;
    int size_str = 0;
    for (int i = 0; i < strlen(line); i++){
        if (line[i] == separator){
            str[size_str] = END_STRING;
            strcpy(city_name, str);
            size_str = 0;
            j++;
        }else{
            str[size_str] = line[i];
            size_str++;
        }
    }
    str[size_str] = END_STRING;
    strcpy(city_value, str);
}

//------------------------------------------------------------------------------//

city_vector_t* get_cities(char* cities_file){
    city_vector_t* cities = city_vector_create();
    if (!cities){
        return NULL;
    }

    printf("Trying to open: %s\n", cities_file);
    int f = open(cities_file, O_RDONLY, 0666);

    if (f < 0) {
	printf("Failed get_cities open\n");
        return NULL;
    }

    int i = 0;
    char line[MAX_SIZE];
    read_line(f, line);

    while((line) && (strcmp(line, "\0") != 0)){
        char city_name[MAX_STRING_SIZE];
        char value_str[MAX_STRING_SIZE];
        split_values(line, ' ', city_name, value_str);

        city_t city = city_create(city_name, value_str);
        if (!city_vector_add(cities, city)){
            city_vector_destroy(cities);
            close(f);
            return NULL;
        }
        read_line(f, line);
        i++;
    }
    close(f);
    return cities;
}

void store_cities(city_vector_t* cities, char* cities_file){
    printf("Trying to open: %s\n", cities_file);
    int f = open(cities_file, O_CREAT || O_WRONLY || O_TRUNC, 0666);

    if (f < 0) {
	printf("Failed store_cities open: %d\n", errno);
        return;
    }

    for (int i = 0; i < city_vector_quantity(cities); i++){
        char line[MAX_SIZE];
        city_t city = city_vector_get(cities, i);
        sprintf(line, "%s %s\n", city_name(city), city_value(city));
        int err = write(f, line, strlen(line));
	if (err < 0)
		printf("Holaaa\n");
    }

    close(f);

    city_vector_destroy(cities);
}
