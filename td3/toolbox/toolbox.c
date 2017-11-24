#include "toolbox.h"

typedef struct tool {
	char *name;
	char *usage;
	int (*main)(int,char *[]);
} tool;

tool tools[]= {
	{ "echo", "write arguments to the standard output", main_echo },
	{ "time", "display execution time", main_time },
	{ "pwd", "display full filename of the current working directory", main_pwd },
	{ "mkdir", "create a new and empty file at given pathname.", main_mkdir },
	{ "false", "alwais fail", main_false },
	{ "rm", "remove file", main_rm },
	{ "rmdir", "remove dir", main_rmdir },
	{ "cat", "write file content to the standard output", main_cat },
	{ "true", "alwais succeed", main_true },
	{ "sh", "a little shell", main_sh },
	{ "mv", "write file content to the standard output", main_mv },
	{ "ls", "a function that is equivalent to ls -li in shell", main_ls },
	{ "cp", "copy given file to specified pathname if possible.", main_cp },
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
