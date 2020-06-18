#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(void) {
  char *ar[4] = {"sequential_min_max", "42", "100", NULL};
  int pid = fork();
  if (pid == 0){
    execv("sequential_min_max", ar);
  }
  wait(NULL);
  printf("Done");
  return 0;
}
