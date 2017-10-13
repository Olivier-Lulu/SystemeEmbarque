#include <stdio.h>
#include "bio.h"

#define SZ 100

int main(int argc, char *argv[])
{
	BFILE *bf;
	ssize_t nb;
	char buf[SZ];
	
	if (argc!=2) {
		fprintf(stderr,"usage: %s filename\n",argv[0]);
		return 1;
	}
	if ((bf=bopen(argv[1],"r"))==NULL) {
		perror("bopen");
		return 2;
	}
	while ((nb=bread(buf,SZ,bf))==SZ)
		fwrite(buf,SZ,1,stdout);
	if (nb>0)
		fwrite(buf,nb,1,stdout);
	if (!beof(bf))
		perror("bread");
	bclose(bf);
	return 0;
}
