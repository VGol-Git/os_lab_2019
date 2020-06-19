CC=gcc
CFLAGS=-I.

.PHONY: all

all: mem

mem : process_memory.o
	$(CC) -o mem process_memory.o $(CFLAGS)

process_memory.o : process_memory.c
	$(CC) -o process_memory.o -c process_memory.c $(CFLAGS)

clean :
	rm mem process_memory.o
