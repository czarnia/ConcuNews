GCC := gcc
CFLAGS := -std=c99 -g -Wall
VFLAGS := --leak-check=full --track-origins=yes --show-leak-kinds=all

SERVERS := echo
DEPS := socket.o server.o


.PHONY: clean valgrind

echo: $(DEPS) echo.c
	$(GCC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(GCC) $(CFLAGS) -c $^

valgrind: echo
	valgrind $(VFLAGS) ./echo

clean:
	rm -f *.o
	rm echo 
