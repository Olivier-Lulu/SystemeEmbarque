#include <sys/errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "bio.h"

BFILE *bopen(const char *filename, const char *mode)
{
  BFILE *stream;
  int flags;
  int fd;
  char md;
	
  if (strcmp(mode,"r") == 0) {
    flags = O_RDONLY;
    md = BMODE_READ;
  } else
    if(strcmp(mode,"w") == 0){
      flags = O_WRONLY;
      md = BMODE_WRITE;
    }else
      if(strcmp(mode,"b") == 0){
	flags = O_RDWR;
	md = BMODE_RDWR;
      }else{
	errno = EINVAL;
	return NULL;
      }
		
  if ((fd = open(filename, flags, PERM_FILE)) == -1)
		return NULL;
	if ((stream=(BFILE *)malloc(sizeof(BFILE)))!=NULL) {
		stream->fd=fd;
		stream->mode=md;
		stream->pos=0;
		stream->currentMode = BMODE_READ;
	}
	return stream;
}

ssize_t bread(void *buf, ssize_t size, BFILE *stream)
{
	char *ptr;
	ssize_t more;

	if ((stream==NULL)||(stream->mode==BMODE_WRITE)) {
		errno = EBADF;
		return 0;
	}
	if(stream->mode==BMODE_RDWR && stream->currentMode==BMODE_WRITE)
	  bflush(buf);
	more=size;
	ptr=buf;

	while (stream->fill - stream->pos < more) {
		memcpy(ptr, &stream->buf[stream->pos], stream->fill - stream->pos);
		ptr += stream->fill - stream->pos;
		more -= stream->fill - stream->pos;
		stream->pos = 0;
		if (( stream->fill = read(stream->fd, stream->buf, BBUFSIZ) ) <= 0) {
			stream->eof = (stream->fill==0);
			stream->fill = 0;
			return size-more;
		}
	}

	memcpy(ptr, &stream->buf[stream->pos], more);
	stream->pos += more;
	return size;
}

int bwrite (void * buf, ssize_t size, BFILE * stream)
{
	if ((stream == NULL) || (stream->mode == BMODE_READ)) {
		errno = EBADF;
		return 0;
	}
	
	if (stream -> eof) {
		errno = EBADFD;
		return 0;
	}

	char * ptr = buf;
	ssize_t further = size;

	if (stream->mode==BMODE_RDWR && stream->currentMode==BMODE_READ){
		stream -> currentMode = BMODE_WRITE;
		bflush(stream);
		lseek(stream -> fd, (- further), SEEK_CUR);
	}

	while (((stream -> pos + stream -> fill) <= further) && (!(stream -> eof))) {
		memcpy(&stream -> but[stream -> pos], ptr, further);
		stream -> pos += further;
		ptr += (stream -> pos + stream -> fill);
		further -= (stream -> pos + stream -> fill);
		bflush(stream);
	}
	
	return size;
}

int bflush (BFILE * stream)
{
  if(write(stream->fd,stream->buf,stream->fill - stream->pos)==-1)
    return -1;
  stream->fill = 0;
  stream->pos = 0;
  return 0;
}

int beof(BFILE *stream)
{
	return stream->eof;
}

int bclose(BFILE *stream)
{
	int r;
	
	if (stream==NULL) {
		errno = EBADF;
		return BEOF;
	}
	if ((r=close(stream->fd))==0)
		free(stream);
	return r;
}
