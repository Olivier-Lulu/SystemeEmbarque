#ifndef _TOOLBOX_H_
#define _TOOLBOX_H_

#include <libgen.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <fcntl.h>
#include <time.h>
#include <pwd.h>
#include <dirent.h>
#include <grp.h>

int main_echo(int, char *[]);

int main_sh(int, char *[]);

int main_false(int, char*[]);

int main_true(int, char*[]);

int main_pwd(int,char*[]);

int main_ls(int,char*[]);
#endif /* _TOOLBOX_H_ */
