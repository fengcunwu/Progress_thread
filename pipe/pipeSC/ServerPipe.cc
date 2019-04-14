
// 这是一个用命名管道实现的服务器端
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define ERR_EXIT(m)\
do{\
  perror(m);\
  exit(EXIT_FAILURE);\
}while(0)

int main()
{
  umask(0);
  if(mkfifo("myfifo", 0644) < 0)
  {
    ERR_EXIT("mkfifo");
  }
  int rfd = open("mypipe", O_RDONLY);
  if(rfd < 0)
  {
    ERR_EXIT("open");
  }
  char buf[1024];
  while(1)
  {
    buf[0] = 0;
    cout << "Please wait..." << endl;

    ssize_t s = read(rfd, buf, sizeof(buf) - 1);
    if(s > 0)
    {
      buf[s - 1] = 0;
      cout << "client say# " << buf << endl;
    }
    else if(s == 0)
    {
      cout << "client quit, exit now! " << endl;
      exit(EXIT_SUCCESS);
    }
    else 
      ERR_EXIT("read");
  }
  close(rfd);
  return 0;
}
