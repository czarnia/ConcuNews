GCC := gcc
CFLAGS := -std=c99 -g -Wall

DEPS := socket.o


.PHONY: clean

server: server.c $(DEPS)
	$(GCC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(GCC) $(CFLAGS) -c $^


clean:
	rm -f *.o
