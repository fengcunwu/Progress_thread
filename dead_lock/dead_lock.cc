//这是一个演示死锁的demo，
//两个线程循环等待对应的互斥锁
//主线程先获取互斥锁a，另一个线程获取互斥锁b
//然后主线程在获取互斥锁b，另一个线程获取互斥锁a
//造成循环等待，出现死锁问题
#include<pthread.h>
#include<unistd.h>
#include<iostream>
#include <stdio.h>

using namespace std;

int a = 0;
int b = 0;

pthread_mutex_t mutex_a;
pthread_mutex_t mutex_b;

void* thread1(void* arg)
{
  pthread_mutex_lock(&mutex_b);
  cout << "in child thread, got mutex_b, waiting for mutex_a" << endl;
  ++b;
  sleep(5);
  pthread_mutex_lock(&mutex_a);
  b += a++;
  pthread_mutex_unlock(&mutex_a);
  pthread_mutex_unlock(&mutex_b);
  pthread_exit(NULL);
}

int main()
{
  pthread_t thread_id;

  pthread_mutex_init(&mutex_a, NULL);
  pthread_mutex_init(&mutex_b, NULL);
  pthread_create(&thread_id, NULL, thread1, NULL);

  pthread_mutex_lock(&mutex_a);
  cout << "in parent thread, got mutex_a, waiting for mutex_b" << endl;
  ++b;
  sleep(5);
  pthread_mutex_lock(&mutex_b);
  b += a++;
  pthread_mutex_unlock(&mutex_b);
  pthread_mutex_unlock(&mutex_a);

  pthread_join(thread_id, NULL);
  pthread_mutex_destroy(&mutex_a);
  pthread_mutex_destroy(&mutex_b);
  return 0;
}
