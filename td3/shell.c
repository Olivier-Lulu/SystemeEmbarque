#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define SZ 1024





/*
 *execute une a une les instructions du fichier (comme main mais avec file a la place de stdin)
 *n'affiche pas de terminal
 */
int parse_scripte(FILE* file){

}

/*
 *cmd arg1 ... argN NULL
 *
 *cd -> changer repertoir
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
 *utiliser par parse_line pour parser les cmd standars
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
    if(*p){
      argv[i++] = p;
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
  simple_cmd(argv);
  return 0;
}

/*
 *utiliser par parse_line pour traiter les affectation de variable
 * une affectation est de la forme nom=valeur
 */
int parse_variable(char* variable,char* valeur){
  setenv(variable,valeur,1);
  return 0;
}
/*
 *parse s et appele simple_cmd
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
