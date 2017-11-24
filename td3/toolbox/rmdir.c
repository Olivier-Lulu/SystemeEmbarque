#include "toolbox.h"

int main_rmdir (const char* file)
{
  if(rmdir(file)){
		return -1;
	} else {
		return EXIT_SUCCESS;
	}
}
