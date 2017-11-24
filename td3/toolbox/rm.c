#include "toolbox.h"

int main_rm (const char* file)
{
  if(unlink(file)){
		return -1;
	} else {
		return EXIT_SUCCESS;
	}
}
