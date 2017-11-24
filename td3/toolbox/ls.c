#include "toolbox.h"

#define isr(x) "-r"[((x)>>2)&01]
#define isw(x) "-w"[((x)>>1)&01]
#define isx(x) "-x"[(x)&01]
#define right(x) isr(x),isw(x),isx(x)
#define allRight(x) right((x)>>6),right((x)>>3),right(x)
#define filetype(x) "?pc?d?b?-?l?s??"[(((x)>>12)&017)]

int main_ls(int argc,char* argv[]){
  DIR* dir = opendir(".");
  struct dirent* file;
  while((file = readdir(dir))!= NULL){
    char* name = malloc(sizeof(char)*1024);
    sprintf(name,"./%s",file->d_name);
    struct stat* stats = malloc(sizeof(struct stat));
    if(lstat(name,stats) == -1){
      perror("lstat");
      return -1;
    }
    /*numero d'I-noeud*/
    printf("%lu ",stats->st_ino);    
    /*type de fichier d=directory -=file l=lien symbolic p=pipe*/
    printf("%c",filetype(stats->st_mode));
    //autorisation
    printf("%c%c%c%c%c%c%c%c%c ",allRight(stats->st_mode));
    //lien
    printf("%lu ",stats->st_nlink);
    // uid
    struct passwd * user = getpwuid(stats->st_uid);
    printf("%s ",user->pw_name);
    //free(user); -> ca crash
    // gid
    struct group * grp = getgrgid(stats->st_gid);
    printf("%s ",grp -> gr_name);
    //free(grp); -> ca crash
    //size
    printf("%lu oct. ",stats->st_size);
    // date
    struct tm * t = gmtime(&stats->st_mtim.tv_sec);
    printf("%d %d:%d ",t->tm_mday,t->tm_hour,t->tm_min);
    //nom
    printf("%s",file->d_name);
    if(S_ISLNK(stats->st_mode)){
      // le fichier est un lien
      char cible[1024];
      int taille = readlink(name,cible,1024);
      cible[taille] = '\0';
      printf(" -> %s",cible);
    }
    printf("\n");
  }
}
