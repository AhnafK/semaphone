#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

int main(){
  long key = 34242;
  long semkey = 42313;
  char *cl = malloc(8);
  printf("Enter: ");
  fgets(cl, 8, stdin);
  //printf("%s",cl);
  if(!strcmp(cl,"-c")){
    shmget(key,1000,IPC_CREAT);
    semget(semkey,1,IPC_CREAT);
    
  }
  else if(!strcmp(cl,"-r")){

  }
  else if(!strcmp(cl,"-v")){

  }
  
  return 0;
}
