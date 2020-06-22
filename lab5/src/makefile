CC=gcc
CFLAGS=-std=c99 -w -lpthread

all : deadlock factorial

deadlock : deadlock.c
	$(CC) -o $@ $^ $(CFLAGS)

factorial : factorial.c
	$(CC) -o $@ $^ $(CFLAGS)