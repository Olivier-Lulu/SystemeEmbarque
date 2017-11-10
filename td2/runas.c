#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[]){
  if(argc < 3){
    fprintf(stderr,"usage: %s [name] [program] [arguments ...]",argv[0]);
    return 1;
  }
  
  char * temp = argv [1];
  argv[1] = argv[2];
  argv[2] = temp;
  execv(argv[1],&argv[2]);
  perror("execl");
  return 1;
}
