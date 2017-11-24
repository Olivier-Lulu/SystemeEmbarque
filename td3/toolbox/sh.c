#include "toolbox.h"

#define SZ 1024
#define MAXARGS 16

int parse_line(char * s);

typedef struct env{
  struct env* next;
  char* variable;
  char* value;
} env;

env * environement = NULL;

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
      /*si autre*/
      if(fork()){
	/*pere*/
	wait(NULL);
	return 0;
      }else{
	execvp(argv[0],argv);
	perror("execvp");
	exit(-1);
      }
    }else{
      /*si exit*/
      exit(0);
    }
  }else{
    /*si cd*/
    chdir(argv[1]);
    return 0;
  }
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

char * getValue(char * variable){
  if(environement){
    env * curr = environement;
    while(strcmp(curr -> variable,variable) && curr -> next)
      curr = curr -> next;
    if(curr)
      return curr -> value;
    else
      return NULL;
  }else
    return NULL;
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
  int j;
  for(j=0;j<i;j++){
    if(*argv[j] == '$'){
      char * valeur = getValue(argv[j]+1);
      if(valeur)
	argv[j] = valeur;
    }else if(!*argv[j]){
      argv[j] = NULL;
      break;
    }
  }

  char* redir_in = strpbrk(s, "<");
  char* redir_out = strpbrk(s, ">");
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
	*redir_out++ = '\0';
	in = redir_in;
	      
	redir_out = strpbrk(redir_out, ">");
	redir_out++;
	while (*redir_out == ' ')
	  redir_out++;
	char* zero_pointer;
	if ((zero_pointer = (strpbrk(redir_out, " "))))
		*zero_pointer = '\0';
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
	*redir_in++='\0';
	out = redir_out;
        
	redir_in = strpbrk(s, "<");
	redir_in++;
	while (*redir_in == ' ')
	  redir_in++;
	char* zero_pointer;
	if ((zero_pointer = (strpbrk(redir_in, " "))))
		*zero_pointer='\0';
	in = redir_in;
	
	return redir_cmd(argv, in, out);
      }
    } else {
      redir_in++;
      while (*redir_in == ' ')
				redir_in++;
			char* zero_pointer;
			if ((zero_pointer = (strpbrk(redir_in, " "))))
				*zero_pointer='\0';
			in = redir_in;
      
      return redir_cmd(argv, in, NULL);
    }
  } else {
    if (redir_out) {
      redir_out++;
      while (*redir_out == ' ')
				redir_out++;
			char* zero_pointer;
			if ((zero_pointer = (strpbrk(redir_out, " "))))
				*zero_pointer='\0';
      
      out = redir_out;
      return redir_cmd(argv, NULL, out);
    }
  }

  int r = simple_cmd(argv);
  free(p);
  return r;
}

/*
 *utilise par parse_line pour traiter les affectations de variable
 * une affectation est de la forme nom=valeur
 */
int parse_variable(char* variable,char* valeur){
  env * new = malloc(sizeof(env));
  new -> next = environement;
  new -> variable =(char*) malloc(sizeof(char)*(strlen(variable)+1));
  strcpy(new -> variable,variable);
  new -> value =(char*) malloc(sizeof(char)*(strlen(valeur)+1));
  strcpy(new -> value,valeur);
  environement = new;
  return 0;
}


int fdpipe;
/*
 *copie du code celene, avec parse-line a la place de execvp
 */
void start_cmd(char* arg)
{
  int fd[2];

  pipe(fd);
  if (fork()) { /* pere */
    close(fd[1]);
    fdpipe=fd[0];
  } else { /* fils */
    dup2(fd[1],STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    parse_line(arg);
    exit(0);
  }
}

/*
 *copie du code celene, avec parse-line a la place de execvp
 */
void next_cmd(char * arg)
{
   int fd[2];

   pipe(fd);
   if (fork()) { /* pere */
     close(fdpipe);
     close(fd[1]);
     fdpipe=fd[0];
   } else { /* fils */
     dup2(fdpipe,STDIN_FILENO);
     dup2(fd[1],STDOUT_FILENO);
     close(fd[0]);
     close(fd[1]);
     close(fdpipe);
     parse_line(arg);
     exit(0);
   }
}

/*
 *copie du code celene, avec parse-line a la place de execvp
 */
void last_cmd(char * arg)
{
  int pid, st;
   if ((pid=fork())) { /* pere */
     close(fdpipe);
     waitpid(pid,&st,0);
   } else { /* fils */
     dup2(fdpipe,STDIN_FILENO);
     close(fdpipe);
     parse_line(arg);
     exit(0);
   }
}

/*parse les cmd utilisant un pipe*/
int parse_pipe(char * s){
  char* p;
  if((p = strpbrk(s,"|")))
    *p = '\0';
  p++;
  char * cmd = s;
  start_cmd(s);
  cmd = p;
  while((p = strpbrk(p,"|"))){
    *p = '\0';
    p++;
    next_cmd(cmd);
    cmd = p;
  }
  last_cmd(cmd);
  return 0;
}

/*
 *parse s et appelle simple_cmd
 */
int parse_line(char * s){
  char * p;
  if((p = strpbrk(s,"\n")))
    *p= '\0';
  if((p = strpbrk(s,"#")))
    *p = '\0';
  p = strpbrk(s,"=");
  if(p && *(p-1) != ' ' && *(p+1) != ' '){
    *p = '\0';
    p++;
    return parse_variable(s,p);
  }else{
    /*p est null donc pas de = */
    if((p = strpbrk(s,"|")))
      /*si contient un pipe*/
      return parse_pipe(s);
    else
      return parse_cmd(s);  
  }
}

int main_sh (int argc,char * argv[]){
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
