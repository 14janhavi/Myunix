#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>

void getdir(){
  DIR *dir = opendir(".");
  if(dir == NULL){
   printf("No files exit\n");
  }

  struct dirent *entry;
  entry = readdir(dir);
  while(entry != NULL){
   if(entry -> d_name[0]!='.'){
     printf("%s\n",entry -> d_name);
    }
    entry = readdir(dir);
  }
  closedir(dir);
}

void gethdir(){
  DIR *dir = opendir(".");
  if(dir == NULL){
   printf("No files exit\n");
  }

  struct dirent *entry;
  entry = readdir(dir);
  while(entry != NULL){
   if(entry -> d_name[0]=='.'){
     printf("%s\n",entry -> d_name);
    }
    entry = readdir(dir);
  }
  closedir(dir);
}

void getindex(){
  DIR *dir = opendir(".");
  if(dir == NULL){
   printf("No files exit\n");
  }

  struct dirent *entry;
  entry = readdir(dir);
  while (entry != NULL) {
    if (entry->d_name[0] != '.') {
      printf("%s\t%ld\n", entry->d_name, entry->d_ino);
    }
    entry = readdir(dir);
  }
  closedir(dir);
}

void fileInfo(){
 DIR *dir = opendir(".");
  if(dir == NULL){
   printf("No files exit\n");
  }
  int ctr=1;
  struct dirent *entry;
  entry = readdir(dir);
  while (entry != NULL) {
    if (entry->d_name[0] != '.') {
      printf("%d\t%s\t%ld\t%d\n",ctr++, entry->d_name, entry->d_ino, entry->d_type );
    }
    entry = readdir(dir);
  }
  closedir(dir);
}

int main(int argc, char *argv[]){
 int opt;
 while((opt = getopt(argc,argv, ":ilaf"))!=-1){
  switch(opt){
    case 'l':
      printf("l flag is used\n");
      getdir();
      break;

    case 'a':
      printf("a flag is used\n");
      gethdir();
      break;

    case 'i':
      printf("i flag is used\n");
      getindex();
      break;
    case 'f':
      printf("f flag is used\n");
      fileInfo();
      break;

    default: 
      printf("Unhandled option");
  }
 }
 for(;optind<argc;optind++){
   printf("Extra argumnets: %s",argv[optind]);
 }
 return 0;
}