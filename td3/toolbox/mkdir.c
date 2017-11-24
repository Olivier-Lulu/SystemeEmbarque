#include "toolbox.h"

int main_mkdir (const char* dir, mode_t mode)
{
	if(mkdir(dir, mode) != 0){
		return -1;
	} else {
		return EXIT_SUCCESS;
	}
	
}
