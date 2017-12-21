# Makefile
.PHONY:
CC=g++ -std=c++11
CFLAGS = -Wall -c -g
all:test
test: test.o config.o
	$(CC) -o test test.o config.o
test.o: test.cpp config.h
	$(CC) $(CFLAGS) test.cpp
config.o: config.cpp config.h
	$(CC) $(CFLAGS) config.cpp
SUBDIR = $(shell ls ./ -R | grep /)
SUBDIRS = $(subst :,/,$(SUBDIR))
SOURCE = $(foreach dir, $(SUBDIRS),$(wildcard $(dir)*.o))
clean:
	rm -rf $(SOURCE)
