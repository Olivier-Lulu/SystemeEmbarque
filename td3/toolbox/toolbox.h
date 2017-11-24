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
#include "bio.h"

int main_echo(int, char *[]);

int main_mkdir(const char*, mode_t);

int main_rmdir(const char*);

int main_link(const char*, const char*);

int main_rm(const char*);

int main_cat(const char*);

int main_cp(const char*, const char*);

int main_false();

int main_ln(const char*, const char*);

int main_ls();

int main_mv(const char*, const char*);

int main_pwd();

int main_sh(int, char* []);

int main_time();

int true();

#endif /* _TOOLBOX_H_ */
