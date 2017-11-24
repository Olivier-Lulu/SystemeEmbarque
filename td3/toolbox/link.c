#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main_link(int argc, char * argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "usage: %s source_file target_file\n", argv[0]);
		exit(1);
	}
	if (link(argv[2],argv[1]) == -1)
	{
		perror("link");
		exit(1);
	}
	return 0;
}
