//这是一个测试pipe的文件，从标准输入(键盘输入)，打印到标准输出上(显示屏上)
//键盘写入数据到管道，读取管道显示在显示屏上
//创建一个匿名管道
// int pipe(int fd[2]);
// fd表示文件描述符组，其中fd[0]表示读端fd[1]表示写端
// 返回值：成功返回0，失败返回错误代码
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <error.h>
#include <string.h>

int main()
{
  int fds[2];
  char buf[100] = {0};
  int len = 0;
  if(pipe(fds) == -1)
  {
    perror("make pipe error");
    exit(0);
  }
  //read from stdin
  // char *fgets(char *buf, int bufsize, FILE *stream);
  // buf 将读到的数据存放到buf中，bufsize指明存储数据的大小，stream文件结构体指针要读取的文件流
  while(fgets(buf, 100, stdin))
  {
    len = strlen(buf);
    //write into pipe
    //ssize_t write (int fd, const void * buf, size_t count); 
    // 把buf中的数据写入到fd所指的文件中，一共写入count个字节
    // 写入成功返回实际写入的数据长度，写入失败返回-1
    if(write(fds[1], buf, len) != len)
    {
      perror("write into pipe error");
      break;
    }
    //清空buf
    memset(buf, 0, sizeof(buf));
    //read from pipe 
    // ssize_t read(int fd, void * buf, size_t count);
    // 从fd所指的文件中读取count个字节到buf中
    // 返回值为实际读取到的字节数, 如果返回0, 表示已到达文件尾或是无可读取的数据。若参数count 为0, 则read()不会有作用并返回0
    // read时fd中的数据如果小于要读取的数据，就会引起阻塞。
    if((len = read(fds[0], buf, 100)) == -1)
    {
      perror("read from pipe erro");
      break;
    }
    
    //write to stdout
    //标准输出文件描述符为1，标准输入文件描述符为0，错误为2
    if(write(1, buf, len) != len)
    {
      perror("write to stdout");
      break;
    }
  }
  return 0;
}
