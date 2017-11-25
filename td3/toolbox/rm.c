#include "toolbox.h"

int main_rm (int argc, char* argv[])
{
	if (argc != 2)
  {
    puts("Bad command use.");
    return -1;
  }
  if(unlink(argv[1])){
		return -1;
	} else {
		return EXIT_SUCCESS;
	}
}
