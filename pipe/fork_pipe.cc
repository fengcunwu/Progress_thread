//这是一个fork和pipe实现的共享管道，
//父进程执行ps -ef  子进程执行 grep ssh
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <error.h>

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
  else if(pid > 0)
  {
    //父进程
    dup2(fds[1], 1);
    close(fds[0]);
    execl("/bin/ps", "ps", "-ef", NULL);
  }
  else 
  {
    // 子进程
    dup2(fds[0], 0);//标准输入重定向到管道的读端, 是系统调用，让一个描述符等效与另一个描述符
    close(fds[1]);
    execl("/bin/grep", "grep","ssh", NULL);
  } 
  return 0;
}

