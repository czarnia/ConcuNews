#include "parser.h"

int main(int argc, char* argv[]) {

	city_vector_t* tmp = get_cities("ciudades.txt");

	store_cities(tmp, "ciudades2.txt");

	return 0;
}
