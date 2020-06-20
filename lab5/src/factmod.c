#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/time.h>

struct BegEnd{
  int res;
  int mod;
  int begin;
  int end;
};

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void PartFact(struct BegEnd* arg);

int main(int argc, char **argv) {

  int k = -1;
  int pnum = -1;
  int mod = -1;
  int res = 1;

 while (1) {

    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"k", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"mod", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            k = atoi(optarg);
            if (k < 0) {
              printf("k is a positive number or zero\n");
              return 1;
            }
            break;
          case 1:
            pnum = atoi(optarg);
            if (pnum <= 0) {
              printf("pnum is a positive number\n");
              return 1;
            }
            break;
           case 2:
            mod = atoi(optarg);
            if (mod <= 0) {
              printf("mod is a positive number\n");
              return 1;
            }
            break;
			break;

          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (k == -1 || pnum == -1 || mod == -1) {
    printf("Wrong args\n");
    return 1;
  }

  if (k == 0) 
  {
    printf("wow so complex, 1\n");
    return 0;
  }
  pthread_t threads[pnum];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
  struct BegEnd* parms = malloc(sizeof(struct BegEnd) * pnum);
  
  if (pnum > k) pnum = k;
  int step = k / pnum; 
  for (int i = 0; i < pnum; ++i){
    parms[i].res = 1;
    parms[i].mod = mod;
    parms[i].begin = step * i + 1;
    parms[i].end = step * (i + 1);
  }
  parms[pnum - 1].end += k - parms[pnum - 1].end;

  for (int i = 0; i < pnum; ++i){
    pthread_create(&threads[i], NULL, (void *)PartFact, (void *)&parms[i]);
  }

  for (int i = 0; i < pnum; ++i){
    pthread_join(threads[i], NULL);
  }

  for (int i = 0; i < pnum; ++i){
    res *= parms[i].res;
  }

  printf("%d\n", res);
return 0;
}

void PartFact(struct BegEnd* arg){
  pthread_mutex_lock(&mut);
  struct BegEnd parm = *arg;
  if (parm.end == parm.begin) {
    parm.res *= parm.begin;
    printf("%d\n", parm.end);
  } else 
  {
    for (int i = parm.begin; i <= parm.end; ++i){
  
      parm.res *= (i % parm.mod);
    }

  }
  *arg = parm;

  pthread_mutex_unlock(&mut);
}

