// 这是一个运用pthread_join和线程退出的demo，
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void *thread1(void *arg)
{
  cout << "thread 1 returning ... " << endl;
  int *p = (int *)malloc(sizeof(int));
  *p = 1;
  return (void *)p;
}

void *thread2(void *arg)
{
  cout << "thread 2 exiting ... " << endl;
  int *p = (int *)malloc(sizeof(int));
  *p = 2;
  pthread_exit((void*)p);
}

void *thread3(void *arg)
{
  while(1)
  {
    cout << "thread 3 is running ..." << endl;
    sleep(2);
  }
  return NULL;
}

int main()
{
  pthread_t tid;
  void *ret;

  // thread 1 return 
  pthread_create(&tid, NULL, thread1, NULL);
  pthread_join(tid, &ret);
  cout << "thread1 id : " << tid << " return code : " << *(int *)ret << endl; 
  free(ret);
  // thread 2 exit 
  pthread_create(&tid, NULL, thread2, NULL);
  pthread_join(tid, &ret);
  cout << "thread2 id : " << tid << " return code : " << *(int *)ret << endl; 
  // thread3 exit by other
  pthread_create(&tid, NULL, thread3, NULL);
  sleep(3);
  pthread_cancel(tid);
  pthread_join(tid, &ret);
  if(ret == PTHREAD_CANCELED)
  {
    cout << "thread3 id : " << tid << " return code : " << PTHREAD_CANCELED << endl;
  }
  else  
    cout << "thread3 id : " << tid << "return code : " << " NULL" << endl;

  return 0;
}
