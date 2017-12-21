# Makefile
CC=g++ -std=c++11
CFLAGS = -Wall -c -g

all:test
test: test.o config.o
	$(CC) -o test test.o config.o
test.o: test.cpp config.h
	$(CC) $(CFLAGS) test.cpp
config.o: config.cpp config.h
	$(CC) $(CFLAGS) config.cpp

.PHONY:
clean:
	rm -f *.o test
