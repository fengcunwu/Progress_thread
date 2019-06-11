#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

#define MAXLEN 1024
#define READ 0
#define WRITE 1


int main()
{
  pid_t pid;
  int fds1[2], fds2[2];
  int x = 0;

  pipe(fds1);
  pipe(fds2);
  pid = fork();

  if(pid < 0)
  {
    perror("fork error");
    exit(0);
  }else if(pid == 0)
  {
    //子进程
    close(fds1[WRITE]);//关闭第一个管道的写描述符，只用第一个管道的读文件描述符
    close(fds2[READ]);//关闭第二个管道的读描述符，只用第二个管道的写文件描述符
    do
    {
       read(fds1[READ], &x, sizeof(int));
       printf("child %d read : %d \n", getpid(), x++);
       write(fds2[WRITE], &x, sizeof(int));
    }while(x <= 8);
    close(fds1[READ]);
    close(fds2[WRITE]);
  }
  else 
  {
    //父进程，fork返回子进程id
    close(fds1[READ]);
    close(fds2[WRITE]);

    x = 0;
    do{
      write(fds1[WRITE], &x, sizeof(int));
      read(fds2[READ], &x, sizeof(int));
      printf("parent %d read : %d \n", getpid(), x++);
    }while(x <= 10);
    close(fds1[WRITE]);
    close(fds2[READ]);
  }
  waitpid(pid, NULL, 0);
  return 0;
}
