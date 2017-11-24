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
#include <unistd.h>
#include "bio.h"

int main_echo(int, char *[]);

int mkdir(const char*, mode_t);

int rmdir(const char*);

int link(const char*, const char*);

int rm(const char*);

#endif /* _TOOLBOX_H_ */
