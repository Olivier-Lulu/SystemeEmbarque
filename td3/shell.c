#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SZ 1024
#define MAXARGS 16

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
 * execute la commande dans argv avec in en fluc d'entree et out en flux de sortie
 */
int redir_cmd(char* argv[], char* in, char* out) {
	int mem_stdin = dup(STDIN_FILENO);
	int mem_stdout = dup(STDOUT_FILENO);
	int fdi, fdo;
  if (in) {
    fdi=open(in, O_RDONLY);
    dup2(fdi, STDIN_FILENO);
  }
  if (out) {
    fdo=open(out, O_CREAT|O_TRUNC|O_WRONLY, 0666);
    dup2(fdo, STDOUT_FILENO);
  }

  int res = simple_cmd(argv);
	
	if(in){
		close(fdi);
		dup2(mem_stdin, STDIN_FILENO);
	}
	if(out){
		close(fdo);
		dup2(mem_stdout, STDOUT_FILENO);
	}

	return res;
}


/*
 *utilise par parse_line pour parser les cmd standards
 */
int parse_cmd(char * s){
  char* argv[MAXARGS];
  char * p = malloc(sizeof(char)*strlen(s));
	strcpy(p,s);
  int i = 1;

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
    if(*p != '>' && *p != '<') {
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

	char* s_copy = malloc(sizeof(char)*strlen(s));
	strcpy(s_copy,s);
  char* redir_in = strpbrk(s_copy, "<");
  char* redir_out = strpbrk(s_copy, ">");
  char* in;
	char* out;

  if (redir_in) {
    if (redir_out) {
      if (redir_in < redir_out){
				redir_in++;
				while (*redir_in == ' ')
					redir_in++;
	
				redir_out--;
				while (*redir_out == ' ')
					redir_out--;
				redir_out++;
				*redir_out = '\0';
				in = redir_in;
				
				redir_out = strpbrk(s, ">");
				redir_out++;
        while (*redir_out == ' ')
					redir_out++;
        out = redir_out;
	
				return redir_cmd(argv, in, out);

      } else {
				redir_out++;
        while (*redir_out == ' ')
					redir_out++;
	
        redir_in--;
        while (*redir_in == ' ')
					redir_in--;
				redir_in++;
        *redir_in='\0';
        out = redir_out;
        
        redir_in = strpbrk(s, "<");
				redir_in++;
        while (*redir_in == ' ')
					redir_in++;
        in = redir_in;
	
        return redir_cmd(argv, in, out);
      }
    } else {
      redir_in++;
      while (*redir_in == ' ')
				redir_in++;
      in = redir_in;
      
      return redir_cmd(argv, in, NULL);
    }
  } else {
    if (redir_out) {
      redir_out++;
      while (*redir_out == ' ')
				redir_out++;
      
      out = redir_out;
      return redir_cmd(argv, NULL, out);
    }
  }
  
  return simple_cmd(argv);
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
