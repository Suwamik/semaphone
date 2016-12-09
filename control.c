#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun{
  int val;
  struct semid_ds *buff;
  unsigned long *buffer;
  struct seminfo *_buf;
};


/// shared memory for how long file 

int main(int argc, char *argv[]){
  int sd;
  int semid;
  int key = ftok("makefile" , 22);
  int key2 = ftok("num" , 22);
  int sc;
  if (strncmp(argv[1], "-c", strlen(argv[1])) == 0){
    umask(0);;
    int fd = open( "text.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    sd = shmget(key2, 5000, IPC_CREAT | 0664);
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0644);
  }
  else if (strncmp(argv[1], "-v", strlen(argv[1])) == 0){
    semid = semget(key, 1, 0);
    sc = semctl(semid, 0, GETVAL);
    printf("semaphore value: %d\n",sc);
  }
  else if(strncmp(argv[1], "-r", strlen(argv[1])) == 0){
    semid = semget(key, 1, 0);
    sc = semctl(semid, 0, IPC_RMID);
    shmctl(shmget(key2,5000), IPC_RMID); //fix
    printf("semaphore removed: %d\n", sc);
	}
  return 0;
}
