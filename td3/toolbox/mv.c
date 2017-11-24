#include "toolbox.h"


int move (const char * src, const char * dst)
{
	int renameResult = rename(src, dst);
	
	if (renameResult == -1)
	{
	  if((copy(src, dst, 0)) != 0){
		if(unlink(src)==-1){
		  perror("unlink");
		  return -1;
		}
	  }else{
		  perror("copy");
		  return -1;
		}
	}
	return 0;
}

int main_mv (int argc, char * argv[])
{
  if(argc != 3){
    printf("%s [sourcefile] [destfile]",argv[0]);
    exit(1);
  }
  if(move(argv[1],argv[2]) != 0){
    perror("move");
    exit(1);
  }
  return 0;
}
