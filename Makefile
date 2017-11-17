GCC := gcc
CFLAGS := -std=c99 -g -Wall

SERVERS := echo
DEPS := socket.o server.o


.PHONY: clean

echo: $(DEPS) echo.c
	$(GCC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(GCC) $(CFLAGS) -c $^


clean:
	rm -f *.o
	rm echo 
