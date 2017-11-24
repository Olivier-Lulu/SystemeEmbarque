#include "toolbox.h"
#define BUFSZ 1024

int copy(const char * src, const char * dst, mode_t mode)
{
	int fhd, fhd_w;
	if ((fhd = open(src, O_RDONLY)) == -1)
	{	
		perror("open src");
		return -1;
	}
	if ((fhd_w = open(dst, O_WRONLY|O_CREAT|O_EXCL, mode)) == -1)
	{       
		perror("open dst");
		return -1;
	}

	void * bufR = malloc(BUFSZ);
	ssize_t isRead = read(fhd, bufR, BUFSZ);

	while (isRead != 0)
	{
		ssize_t isWritten = write(fhd_w, bufR, isRead);
		if (isWritten < isRead)
		{
			free (bufR);
			errno = EDQUOT;
			return -1;
		}
		isRead = read(fhd, bufR, BUFSZ);
	}

	close (fhd);
	close (fhd_w);
	free (bufR);
	return isRead;
}

int main_cp(const char* source, const char* dest)
{
	if (copy(source, dest, 0666) != 0)
	{
		perror("copy");
		exit(2);
	} 
	return(EXIT_SUCCESS);
}
