// 这是一个操作共享变量会有问题的售票系统代码
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <string>

using namespace std;

int ticket = 20;
//pthread_mutex_t mutex;

void *route(void *arg)
{
  char *id = (char*)arg;
  while(1)
  {
    //pthread_mutex_lock(&mutex);
    if(ticket > 0)
    {
      usleep(1000);
      cout << id << "  sells ticket:  " << ticket << endl;
      ticket--;
      //pthread_mutex_unlock(&mutex);
      sleep(1);
    }
    else 
    {
      //pthread_mutex_unlock(&mutex);
      break;
    }
  }  
}

int main()
{
  pthread_t t1, t2, t3, t4;
  char *p1 = "thread1";
  char *p2 = "thread2";
  char *p3 = "thread3";
  char *p4 = "thread4";

  //pthread_mutex_init(&mutex, NULL);

  pthread_create(&t1, NULL, route, p1);
  pthread_create(&t3, NULL, route, p3);
  pthread_create(&t2, NULL, route, p2);
  pthread_create(&t4, NULL, route, p4);
  
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);

  //pthread_mutex_destroy(&mutex);
  return 0;
}
