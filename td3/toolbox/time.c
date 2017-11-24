#include "toolbox.h"

int main_time(int argc, char* argv[]){
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
    printf("user time: %lu\n",t -> tms_cutime);
    printf("system time: %lu\n",t -> tms_cstime);
    free(t);
    return 0;
  }else{
    execv(argv[1],&argv[2]);
    perror("execv");
    return -1;
  }
}
