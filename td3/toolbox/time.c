#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>

int main(int argc, char* argv[]){
  if(argc < 2){
    printf("%s [programe]\n",argv[0]);
    return -1;
  }

  int pid;
  if((pid=fork())){
    int status;
    waitpid(pid,&status,0);
    struct tms * t =(struct tms *) malloc(sizeof(struct tms));
    times(t);
    printf("user time: %d\n",t -> tms_cutime);
    printf("system time: %d\n",t -> tms_cstime);
    free(t);
    return 0;
  }else{
    execv(argv[1],&argv[2]);
    perror("execv");
    return -1;
  }
}
