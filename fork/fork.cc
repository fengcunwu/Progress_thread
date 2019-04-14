#include <unistd.h>
#include <error.h>
#include <iostream>
using namespace std;
#if 0
int main () 
{ 
  pid_t fpid; //fpid表示fork函数返回的值
  int count=0;
  fpid=fork(); 
  if (fpid < 0) 
    cout << "error fork" << endl; 
  else if (fpid == 0) {
        cout << "i am child process, pid = " << getpid() << endl;
        count++;
  }
  else {
        cout << "i am father process, pid = " << getpid() << endl;
        count++;          
                  
  }
  cout << "一共创建了: " << count << "个进程" << endl;
  return 0;
}
#endif
#if 0
int main()
{
  fork();
  fork();
  fork();
  fork();
  cout << "hello" << endl;
  return 0;
}
#endif 
#include <stdio.h>
int main()
{
  pid_t pid = fork();
  if(pid > 0)
  {
    //父进程
    cout << "子进程id:" << pid << endl;
  }
  else if(pid == 0)
  {
    cout << "子进程getpid()" << getpid() << endl;
  }
  else 
  {
    perror("fork error");
  }
  return 0;
}
