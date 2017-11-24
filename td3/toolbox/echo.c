#include "toolbox.h"

int main_echo(int argc, char *argv[])
{
	int i;
	
	for(i=1;i<argc-1;i++)
		printf("%s ",argv[i]);
	if (argc>1)
		puts(argv[argc-1]);
	else
		puts("");
	return EXIT_SUCCESS;
}
