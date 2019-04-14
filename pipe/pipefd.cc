//这是一个用pipe和fork共同实现的共享管道
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>

using namespace std;

int main()
{
  int fds[2];
  if(pipe(fds) == -1)
  {
    perror("pipe error");
    exit(0);
  }

  pid_t pid;
  pid = fork();
  if(pid < 0)
  {
    perror("fork error");
    exit(1);
  }
  else if(pid == 0)
  {
    //子进程
    close(fds[0]);
    write(fds[1], "hello", 5);
    exit(2);
  }
  else 
  {
    //父进程
    close(fds[1]);
    char buf[10] = {0};
    read(fds[0], buf, 5);
    cout << buf << endl;
  }
  return 0;
}
