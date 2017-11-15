#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define SZ 1024

/*
 *cmd arg1 ... argN NULL
 *
 *cd -> changer repertoire
 *exit -> couper prog
 *autre -> fork, execute, wait
 */
int simple_cmd(char* argv[]){
  int different = strcmp(argv[0],"cd");
  if(different){
    different = strcmp(argv[0],"exit");
    if(different){
      //si autre
      if(fork()){
	//pere
	wait(NULL);
	return 0;
      }else{
	//fils
	FILE* file = fopen(argv[0],"r");
	if(file){
	  parse_scripte(file);
	  fclose(file);
	  return 0;
	}else{
	  execvp(argv[0],argv);
	  perror("execvp");
	  exit(-1);
	}
      }
    }else{
      //si exit
      exit(0);
    }
  }else{
    //si cd
    chdir(argv[1]);
    return 0;
  }
}

/*
 * execute la commande dans argv avec in en fluc d'entree et out en flux de sortie
 */
int redir_cmd(char* argv[], char* in, char* out) {

}


/*
 *utilise par parse_line pour parser les cmd standards
 */
int parse_cmd(char * s){
  char* argv[16];
  char * p = s;
  int i = 1;

  argv[0] = s;
  p = strpbrk(p,"\n");
  if(p)
    *p = '\0';
  p = s;
  while((p = strpbrk(p," "))){
    *p = '\0';
    p++;
    while(*p && *p==' ' && *p != '#')
      p++;
    if(*p == '#')
      break;
    if(*p != ">" && *p= "<") {
      argv[i++] = p;
		} else {
			break;
		}
  }
  argv[i] = NULL;
  for(int j=0;j<i;j++){
    if(*argv[j] == '$'){
      char * valeur = getenv(argv[j]+1);
      if(valeur)
				argv[j] = valeur;
    }
  }

	char* redir_in = strpbrk(s, "<");
	char* redir_out = strpbrk(s, ">");
	char* in, out;

	if (redir_in) {
		if (redir_out) {
			if (redir_in < redir_out){
				redir_in++;
				while (*redir_in++ == " ");

				redir_out--;
				while (*redit_out-- == " ");
				++redir_out='\0';
				in = redir_in;

				redir_out++ = strpbrk(s, ">");
        while (*redit_out++ == " ");
        out = redir_out;

				redir_cmd(argv, in, out);
			} else {
				redir_out++;
        while (*redir_out++ == " ");

        redir_in--;
        while (*redit_in-- == " ");
        ++redir_in='\0';
        out = redir_out;
        
        redir_in++ = strpbrk(s, "<");
        while (*redit_in++ == " ");
        in = redir_out;

        redir_cmd(argv, in, out);
				return 0;
			}
		} else {
			redir_in++;
			while (*redir_in++ == " ");
			in = redir_in;

			redir_cmd(argv, in, NULL);
			return 0;
		}
	} else {
		if (redir_out) {
			redir_out++;
			while (*redir_out++ == " ");

			out = redir_out;
			redir_cmd(argv, NULL, out);
		}
	}

  simple_cmd(argv);
  return 0;
}

/*
 *utilise par parse_line pour traiter les affectations de variable
 * une affectation est de la forme nom=valeur
 */
int parse_variable(char* variable,char* valeur){
  setenv(variable,valeur,1);
  return 0;
}

/*
 *parse s et appelle simple_cmd
 */
int parse_line(char * s){
  char * p;
  p = strpbrk(s,"\n");
  if(p)
    *p = '\0';

  p = strpbrk(s,"=");
  if(p && *(p-1) != ' ' && *(p+1) != ' '){
    *p = '\0';
    p++;
    return parse_variable(s,p);
  }else{
    //p est null donc pas de =
    return parse_cmd(s);  
  }
}

int main (int argc,char * argv[]){
  char buf[SZ];
  while(1){
    printf("$");
    fflush(stdout);
    fgets(buf,SZ,stdin);
    parse_line(buf);
  }
}
