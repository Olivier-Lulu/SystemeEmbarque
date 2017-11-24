#include "toolbox.h"

typedef struct tool {
	char *name;
	char *usage;
	int (*main)(int,char *[]);
} tool;

tool tools[]= {
	{ "echo", "write arguments to the standard output", main_echo },
	{ NULL, NULL, NULL }
};

int main(int argc, char *argv[])
{
	int i=0;
	char *name;
	
	name = basename(argv[0]);
	while ((tools[i].name != NULL) && strcmp(name, tools[i].name))
		i++;
	if (tools[i].name != NULL)
		return tools[i].main(argc, argv);
	else {
		fprintf(stderr, "usage: tool arg1 ... argN\nwhere tool is a valid tool name among:\n");
		for (i=0; tools[i].name != NULL; i++)
			fprintf(stderr, "    %s -- %s\n", tools[i].name, tools[i].usage);
		return EXIT_FAILURE;
	}
}