#ifndef _BIO_H_
#define _BIO_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BBUFSIZ	1024
#define PERM_FILE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

#define BEOF (-1)

#define BMODE_READ 'r'
#define BMODE_WRITE 'w'
#define BMODE_RDWR 'b'

typedef struct {
	int fd;
	char mode;
	char currentMode;
	int eof;
	ssize_t fill;
	ssize_t pos;
	unsigned char buf[BBUFSIZ];
} BFILE;

BFILE *bopen(const char *filename, const char *mode);
ssize_t bread(void *buf, ssize_t size, BFILE *stream);
int beof(BFILE *stream);
int bclose(BFILE *stream);
int bwrite (void *buf, ssize_t size, BFILE *stream);
int bflush (BFILE * stream);

#endif /* _BIO_H_ */
