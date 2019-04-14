#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>
#define gettid() syscall(__NR_gettid)

using namespace std;

void *rout(void *arg)
{
  int i = 0;
  for( ; ; )
  {
    cout << "i am thread" << endl;
    sleep(1);
  }
}
int main()
{
  pthread_t tid;
  int ret = 0;
  if((ret = pthread_create(&tid, NULL, rout, NULL) != 0))
  {
    cerr << "pthread_create error" << endl;
    exit(0);
  }
  cout << tid << endl;
  cout << pthread_self() << endl;
  cout << gettid() << endl;
  cout << getpid() << endl;
  int i = 0;
  for( ; ; )
  {
    cout << "i am main thread" << endl;
    sleep(1);
  }
  return 0;
}
