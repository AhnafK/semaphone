#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
			      (Linux-specific) */
};

int main(int argc, char* argv[]){
  long key = 34242;
  long semkey = 42313;
  char *cl;
  if(argc < 2){
    cl = malloc(8);
    printf("Enter: ");
    fgets(cl, 3, stdin);
    printf("%s|\n",cl);
  }else{
    cl = argv[1];
  }
  if(!strcmp(cl,"-c")){
    printf("start\n");
    int shm_id = shmget(key,1000,IPC_CREAT|IPC_EXCL|0666);
    int semid = semget(semkey,1,IPC_CREAT|IPC_EXCL|0666);
    union semun q;
    q.val = 1;
    semctl(semid, 0, SETVAL, q);
    int fd = open("story.txt", O_CREAT | O_TRUNC,0666);
    printf("done\n");
  }
  else if(!strcmp(cl,"-r")){
    int shm_id = shmget(key,1000,IPC_CREAT|IPC_EXCL|0666);
    int semid = semget(semkey,1,IPC_CREAT|IPC_EXCL|0666);
    shmctl(shm_id, IPC_RMID, NULL);
    
    int fd = open("story.txt",O_RDONLY);
    char *storie = malloc(1024);
    read(fd, storie, 1024);
    printf("\n%s\n",storie);
  }
  else if(!strcmp(cl,"-v")){
    int fd = open("story.txt",O_RDONLY);
    char *storie = malloc(1024);
    read(fd, storie, 1024);
    printf("\n%s\n",storie);
  }
  else{
    printf("fail\n");
    return -1;
  }
  
  return 0;
}
