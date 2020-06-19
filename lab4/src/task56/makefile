CC=gcc
CFLAGS=-I. -L./
LIBS = -lpthread -lsum.a

.PHONY: all

all: parallel_sum

parallel_sum : utils.o utils.h 
	$(CC) -o parallel_min_max utils.o $(CFLAGS)

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

clean :
	rm utils.o parallel_sum
