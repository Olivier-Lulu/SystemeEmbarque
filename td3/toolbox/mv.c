#include "toolbox.h"


int move (const char * src, const char * dst)
{
	int res = rename(src, dst);
	
	if (res == -1)
	  {
	    res = main_cp(src, dst);
	    
	    if (!res){ /*if res is anything but 0, copy failed*/
	      unlink(src);
	    }
	  }
	
	return res;
}

int main_mv (const char* src, const char * dst)
{
  if(argc != 3){
    printf("%s [sourcefile] [destfile]",argv[0]);
    exit(1);
  }
  if (move(src, dst)){ /*as copy, move return 0 (false) upon success*/
    puts("mv command failed");
    return -1;
  }
  
  return EXIT_SUCCESS;
}
