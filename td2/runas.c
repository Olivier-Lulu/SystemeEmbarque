#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[]){
  char * temp = argv [1];
  argv[1] = argv[2];
  argv[2] = temp;
  execv(argv[1],&argv[2]);
  perror("execl");
  return 1;
}
