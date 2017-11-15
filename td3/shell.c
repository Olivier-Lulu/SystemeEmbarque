#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define SZ 1024

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
	execvp(argv[0],argv);
	perror("execvp");
	exit(-1);
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

//parse les cmd utilisant un pipe
int parse_pipe(char * s){
  /*int pipes [2];
  if(!(pipe(pipes))){
    perror("pipe");
    exit(1);
  }
  char* p;
  if((p = strbrk(s,"|")))
    *p = '\0';
  p++;
  char * cmd1 = s;
  if(fork()){

  }else{
    write(pipes[0]);
    char * argv[2];
    argv[0] = "shell";
    argv[1] = pipes[1];
    execvp("shell",argv);
    perror("execvp");
    exit(-1);
    }*/
  return 0;
}

/*
 *utiliser par parse_line pour parser les cmd standards
 */
int parse_cmd(char * s){
  char* argv[16];
  char * p;
  int i = 1;
  p = s;
  while(*p && *p==' ')
    p++;
  if(!*p)
    return 0;
  argv[0] = p;
  while((p = strpbrk(p," "))){
    *p = '\0';
    p++;
    while(*p && *p==' ')
      p++;
    if(*p)
      argv[i++] = p;
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
  if((p = strpbrk(s,"\n")))
    *p = '\0';
  if((p = strpbrk(s,"#")))
    *p = '\0';
  p = strpbrk(s,"=");
  if(p && *(p-1) != ' ' && *(p+1) != ' '){
    *p = '\0';
    p++;
    return parse_variable(s,p);
  }else{
    //p est null donc pas de =

    if((p = strpbrk(s,"|")))
      //si contient un pipe
      return parse_pipe(s);
    else
      return parse_cmd(s);  
  }
}


int main (int argc,char * argv[]){
  FILE* fd = stdin;
  if(argc == 2)
    if((fd = fopen(argv[1],"r")) == NULL){
      perror("fopen");
      exit(1);
    }
  char buf[SZ];
  while(!feof(fd)){
    if(fd == stdin)
      printf("$");
    fflush(stdout);
    fgets(buf,SZ,fd);
    parse_line(buf);
  }
  fclose(fd);
  exit(0);
}
