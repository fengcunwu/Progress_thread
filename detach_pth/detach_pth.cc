//这是一个实践pthread_detach的demo，新创建的线程和main线程是同步执行的，
//也就是说在主线程中直接等待新线程是可以的，因为新建的线程还没走到分离的那一步
//如果在main线程中sleep(3)可以看出效果，被分离的线程不能被等待，会等待失败

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <error.h>

void *thread_run( void * arg)
{
  if(pthread_detach(pthread_self()) == 0)
    printf("%s\n", (char*)arg);
  return NULL;
}

int main()
{
  pthread_t tid;
  char * pch= "thread run ...";
  if(pthread_create(&tid, NULL, thread_run, pch) != 0)
  {
    perror("pthread_create error");
    exit(1);
  }
  sleep(3);
  int ret = 0;
  if(pthread_join(tid, NULL) == 0)
  {
    printf("pthread_join success\n");
    ret = 0;
  }
  else{
    printf("pthread_join failed\n");
    ret = 1;
  }
  return 0;
}
