#include <toolbox.h>


int move (const char * src, const char * dst)
{
	int renameResult = rename(src, dst);
	
	if (renameResult == -1)
	{
		copy(src, dst, mode);
		//si pas d'erreurs de copy
		//unlink(src);
	}

	//return copy ou unlink result
	return 0;
}

int main_mv (int argc, char * argv[])
{
	//traitement entree
	//utilisation de perror
}
