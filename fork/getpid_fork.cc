#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

using namespace std;

int g_val = 0;
int main()
{
  pid_t tid = fork();
  if(tid < 0)
  {
    perror("fork error");
    exit(0);
  }
  else if(tid == 0)
  {
    printf("child[%d]: %d : %p\n", getpid(), g_val, &g_val);
  }
  else 
  {  
    printf("parent[%d]: %d : %p\n", getpid(), g_val, &g_val);
  }
  sleep(1);
  return 0;
}
