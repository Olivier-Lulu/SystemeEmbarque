#include "toolbox.h"

int main_mkdir (const char* dir, mode_t mode)
{
	if (argc < 2) {
		puts("Bad command use");
		return -1;
	}

	mode_t mode;
	if (argv[2])
	  mode =*(argv[2]);
	else
		mode = 0777;

	if(mkdir(argv[1], mode) != 0){
		return -1;
	} else {
		return EXIT_SUCCESS;
	}
	
}
