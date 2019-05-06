#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define CONSUMERS_COUNT 2
#define PRODUCERS_COUNT 2

struct msg{
  struct msg *next;
  int num;
};

struct msg *head = NULL;

pthread_cond_t cond;
pthread_mutex_t mutex;
pthread_t threads[CONSUMERS_COUNT+PRODUCERS_COUNT];

void* consumer(void *p)
{
  int num = *(int*)p;
  free(p);
  struct msg *mp;
  for(; ; )
  {
    pthread_mutex_lock(&mutex);
    while(head == NULL)//没有数据只能等待
    {
      printf("%d begin wait a cond...\n", num);
      pthread_cond_wait(&cond, &mutex);//阻塞等待，直到条件满足，另一个唤醒本线程
    }
    printf("%d end wait a cond...\n", num);
    printf("%d begin consume produce...\n", num);
    mp = head;// 线程被唤醒，说明head有数据，取出其中的数据，并指向下一个节点
    head = mp->next;
    pthread_mutex_unlock(&mutex);
    printf("Consume %d\n", mp->num);//打印取出来的数据
    sleep(rand()%5);
  }
}

void* producer(void *p)
{
  struct msg *mp;
  int num = *(int*)p;
  free(p);
  for(; ; )
  {
    printf("%d begin produce product...\n", num);
    mp = (struct msg*)malloc(sizeof(struct msg));
    mp->num = rand()%1000 + 1;//随机生产数据
    printf("produce %d\n", mp->num);
    pthread_mutex_lock(&mutex);
    mp->next = head;
    head = mp;//把数据给head，
    printf("%d end produce product...\n", num);
    pthread_cond_signal(&cond);//生产了数据，唤醒等待的线程，
    pthread_mutex_unlock(&mutex);
    sleep(rand()%5);
  }
}

int main()
{
  srand(time(NULL));

  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&mutex, NULL);

  int i = 0;
  for(i = 0; i < CONSUMERS_COUNT; i++)
  {
    int *p = (int*)malloc(sizeof(int));
    *p = i;
    pthread_create(&threads[i], NULL, consumer, (void*)p);
  }

  for(i = 0; i < PRODUCERS_COUNT; i++)
  {
    int *p = (int*)malloc(sizeof(int));
    *p = i;
    pthread_create(&threads[i], NULL, producer, (void*)p);
  }

  for(i = 0; i < CONSUMERS_COUNT + PRODUCERS_COUNT; i++)
  {
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  return 0;
}
