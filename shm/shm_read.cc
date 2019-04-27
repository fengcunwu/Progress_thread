/* 共享内存的使用流程
 * 1,创建共享内存                                shmget
 * int shmget(key_t key, size_t size, int shmflg);
 *  key    共享内存标识符
 *  size   共享内存大小
 *  shmflg 打开方式/创建权限
 *  返回值: 成功返回一个shmid  失败返回-1；
 * 2,将共享内存映射到虚拟地址空间                shmat
 * 3,对共享内存进行操作                          memcpy....................
 * 4,解除映射关系                                shmdt
 * 5,删除共享内存                                shmctl
 *   */


#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <errno.h> 


#define IPC_KEY 0x12345678
#define PROJ_ID 12345
#define SHM_SIZE 4096

int main()
{
  int shmid;
  //创建共享内存
  // key_t key = ftok(".", PROJ_ID);
  shmid = shmget(IPC_KEY, SHM_SIZE, IPC_CREAT | 0666); // 创建共享内存，并且指定大小和权限
  if(shmid < 0)
  {
    perror("shmget error");
    exit(0);
  }
  //将共享内存映射到虚拟地址空间上
  char* shm_start = (char *)shmat(shmid, NULL, 0);
  if(shm_start == (void*)-1)
  {
    perror("shmat error");
    exit(1);
  }
  //进行相关的操作
  int i = 0;
  while(1)
  {
    printf("%s\n", shm_start);
    sleep(1);
  }
  //解除映射关系
  shmdt(shm_start);
  //删除共享内存
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}
