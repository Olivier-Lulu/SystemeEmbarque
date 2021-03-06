#include "toolbox.h"

#define SZ 1024

int main_cat(int argc, char* argv[])
{
	if (argc!=2) {
		fprintf(stderr,"usage: %s filename\n",argv[0]);
		return 1;
	}
	
	BFILE *bf;
	ssize_t nb;
	char buf[SZ];
	
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
	return EXIT_SUCCESS;
}
