#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>


pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;

void todo1(){
  pthread_mutex_lock(&mut1); //блокируем mut1 и спим 1 секунду
  sleep(1);
  pthread_mutex_lock(&mut2); //блокируем mut2 
  pthread_mutex_unlock(&mut1);
  pthread_mutex_unlock(&mut2);
}
void todo2(){
  pthread_mutex_lock(&mut2);//блокируем mut2 и спим 1 секунду
  sleep(1);
  pthread_mutex_lock(&mut1);//блокируем mut1
  pthread_mutex_unlock(&mut2);
  pthread_mutex_unlock(&mut1);
  }

int main(){
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, (void *)todo1, NULL);
  pthread_create(&thread2, NULL, (void *)todo2, NULL);

  pthread_join(thread1, NULL) ;
  pthread_join(thread2, NULL);

  return 0;
}
