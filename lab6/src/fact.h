#ifndef FACT_H
#define FACT_H
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <getopt.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

#include "pthread.h"


struct FactorialArgs {
  uint64_t begin;
  uint64_t end;
  uint64_t mod;
};

struct Server {
  char ip[255];
  int port;
  struct FactorialArgs args;
};

uint64_t MultModulo(uint64_t a, uint64_t b, uint64_t mod);

bool ConvertStringToUI64(const char *str, uint64_t *val);

#endif
