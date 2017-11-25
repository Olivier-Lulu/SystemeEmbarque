#ifndef _TOOLBOX_H_
#define _TOOLBOX_H_

#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "bio.h"

int main_time(int, char*[]);

int main_true(int,char*[]);

int main_false(int,char*[]);

int main_echo(int, char *[]);

int main_pwd(int,char*[]);

int main_ls(int,char*[]);

int main_cp(int, char *[]);

int main_mkdir(int, char*[]);

int main_rmdir(int, char*[]);

int main_link(int, char*[]);

int main_rm(int, char*[]);

int main_cat(int, char*[]);

int main_cp(int, char*[]);

int main_mv(int, char*[]);

int main_sh(int, char* []);

int main_time(int, char* []);

#endif /* _TOOLBOX_H_ */
