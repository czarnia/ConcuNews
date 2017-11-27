GCC := gcc
CFLAGS := -std=c99 -g -Wall
VFLAGS := --leak-check=full --track-origins=yes --show-leak-kinds=all

DEPS := socket.o server.o city.o parser.o service.o

.PHONY: clean valgrind

main: $(DEPS) main.c
	$(GCC) $(CFLAGS) $^ -o $@

currency_service: $(DEPS) currency_service.c
	$(GCC) $(CFLAGS) $^ -o $@

temperature_service: $(DEPS) temperature_service.c
	$(GCC) $(CFLAGS) $^ -o $@

main_server: $(DEPS) main_server.c
	$(GCC) $(CFLAGS) $^ -o $@

client: $(DEPS) client.c
	$(GCC) $(CFLAGS) $^ -o $@

echo: $(DEPS) echo.c
	$(GCC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(GCC) $(CFLAGS) -c $^

valgrind: main
	valgrind $(VFLAGS) ./main

clean:
	rm -f *.o
	rm echo 
