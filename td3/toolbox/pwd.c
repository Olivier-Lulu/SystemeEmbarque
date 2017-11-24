#include "toolbox.h"

#define BUFFSZ 1024

int main_pwd(int argc,char* argv[]){
  char* dir = (char*) malloc(sizeof(char) * BUFFSZ);
  size_t size = BUFFSZ;
  while(getcwd(dir,size) == NULL){
    if(errno == ERANGE){
      size += 2 * BUFFSZ;
      dir = realloc(dir,size);
    }else{
      perror("getcwd");
      exit(1);
    }
  }
  fprintf(stdout,"%s\n",dir);
  free(dir);
  return 0;
}
