#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "pthread.h"
#include "fact/fact.h"

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;



void *Factorial(void *args) {
    //pthread_mutex_lock(&mut);
    struct Server *to = (struct Server *)args;
    uint64_t answer = 0;
    struct hostent *hostname = gethostbyname(to->ip);
    if (hostname == NULL) {
      fprintf(stderr, "gethostbyname failed with %s\n", to->ip);
      exit(1);
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(to->port);
    server.sin_addr.s_addr = *((unsigned long *)hostname->h_addr);

    int sck = socket(AF_INET, SOCK_STREAM, 0);
    if (sck < 0) {
      fprintf(stderr, "Socket creation failed!\n");
      exit(1);
    }

    if (connect(sck, (struct sockaddr *)&server, sizeof(server)) < 0) {
      fprintf(stderr, "Connection failed\n");
      exit(1);
    }
    
    uint64_t begin = to->args.begin;
    uint64_t end = to->args.end;
    uint64_t mod = to->args.mod;

    char task[sizeof(uint64_t) * 3];
    memcpy(task, &begin, sizeof(uint64_t));
    memcpy(task + sizeof(uint64_t), &end, sizeof(uint64_t));
    memcpy(task + 2 * sizeof(uint64_t), &mod, sizeof(uint64_t));

    if (send(sck, task, sizeof(task), 0) < 0) {
      fprintf(stderr, "Send failed\n");
      exit(1);
    }

    char response[sizeof(uint64_t)];
    if (recv(sck, response, sizeof(response), 0) < 0) {
      fprintf(stderr, "Recieve failed\n");
      exit(1);
    }
    
    memcpy(&answer, response, sizeof(uint64_t));
    //printf("answer: %llu\n", answer);

    close(sck);
  //pthread_mutex_unlock(&mut);
  return (void *)(uint64_t *)answer;
}

int main(int argc, char **argv) {
  uint64_t k = -1;
  uint64_t mod = -1;
  char servers[255] = {'\0'}; //т.к. в некоторых файловых системах максимаьная длина имени файла не может превышать 255 символов
  int servers_num = -1;

  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"k", required_argument, 0, 0},
                                      {"mod", required_argument, 0, 0},
                                      {"servers", required_argument, 0, 0},
                                      {"serversnum", required_argument, 0, 0},                                                    
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, &option_index);

    if (c == -1)
      break;

    switch (c) {
    case 0: {
      switch (option_index) {
      case 0:
        ConvertStringToUI64(optarg, &k);
        if (k < 0)
        {
            printf("k is a positive integer number or zero");
            return 1;
        }
        break;
      case 1:
        ConvertStringToUI64(optarg, &mod);
        if (mod < 1)
        {
            printf("k is a positive integer number");
            return 1;
        }
        break;
      case 2:
        memcpy(servers, optarg, strlen(optarg));
        break;
      case 3:
        servers_num = atoi(optarg);
        if (servers_num < 1)
        {
            printf("serversnum is a positive integer number");
            return 1;
        }
        break;
      default:
        printf("Index %d is out of options\n", option_index);
      }
    } break;

    case '?':
      printf("Arguments error\n");
      break;
    default:
      fprintf(stderr, "getopt returned character code 0%o?\n", c);
    }
  }

  if (k == -1 || mod == -1 || !strlen(servers)) {
    fprintf(stderr, "Using: %s --k 1000 --mod 5 --servers /path/to/file --serversnum 3\n",
            argv[0]);
    return 1;
  }
  
  struct Server *to = malloc(sizeof(struct Server) * servers_num);
  pthread_t threads[servers_num];
  uint64_t step = k / servers_num;

  for (int i = 0; i < servers_num; i++) {
    memcpy(to[i].ip, "127.0.0.1", sizeof("127.0.0.1"));
    to[i].port = 20000 + i;
    to[i].args.begin = step * i;
    to[i].args.mod = mod;
    if (i == servers_num - 1)
    {
      to[i].args.end = k;
    }
    else
    {
      to[i].args.end = step * (i + 1);
    }
    if (pthread_create(&threads[i], NULL, Factorial, (void *)&to[i])) {
        printf("Error: pthread_create failed!\n");
        return 1;
    }
  }

  uint64_t total = 1;
  for (uint32_t i = 0; i < servers_num; i++) {
    uint64_t result = 0;
    pthread_join(threads[i], (void **)&result);
    total = MultModulo(total, result, mod);
  }
    
  printf("answer: %llu\n", total);
  free(to);

  return 0;
}
