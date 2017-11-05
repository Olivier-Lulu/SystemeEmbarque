#include <stdio.h>
#include "bio.h"

#define BUFFSZ 1024



int main(int argc,char* argv[]){
  if(argc != 3){
    fprintf(stderr,"usage: %s sourceFile targetFile\n",argv[0]);
    return 1;
  }
  BFILE* source;
  if((source = bopen(argv[1],"r")) == NULL){
    perror("bopen");
    return 2;
  }
  BFILE* cible;
  if((cible = bopen(argv[2],"w")) == NULL){
    bclose(source);
    perror("bopen");
    return 2;
  }
  char buf[BUFFSZ];
  ssize_t tailleLue = 1;
  ssize_t tailleEcrie;
  while(!beof(source) && tailleLue != 0){
    tailleLue = bread(buf,BUFFSZ,source);
    tailleEcrie = bwrite(buf,tailleLue,cible);
    if(tailleEcrie != tailleLue){
      perror("bwrite");
      break;
    }
  }
  bflush(cible);
  bclose(source);
  bclose(cible);
  return 0;
}

