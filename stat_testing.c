#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>

void return_size(char *file){
  struct stat sb;
  stat(file, &sb);
  size_t size = sb.st_size;
  printf("File size: %lu \n", size);
}

void return_mode(char *file){
  struct stat sb;
  stat(file, &sb);
  mode_t permissions = sb.st_mode;
  printf("File permissions: %o \n", permissions);
}

void return_time(char *file){
  struct stat sb;
  stat(file, &sb);
  char *last_access = ctime(&sb.st_atime);
  printf("Time of last access: %s \n", last_access);
}

void readable_size(char *file){
  struct stat sb;
  stat(file, &sb);
  size_t size = sb.st_size;
  int gb = size / 1024;
  size = size % 1024;
  int mb = size / 1024;
  size = size % 1024;
  int kb = size / 1024;
  size = size % 1024;
  int b = size;
  printf("Readable file size: %d GB %d MB %d KB %d B\n",gb,mb,kb,b);
}

char* get_permissions(int p){
  if(p == 1)
    return "--x";
  if(p == 2)
    return "-w-";
  if(p == 3)
    return "-wx";
  if(p == 4)
    return "r--";
  if(p == 5)
    return "r-x";
  if(p == 6)
    return "rw-";
  return "rwx";
}

void readable_permissions(char *file){
  struct stat sb;
  stat(file, &sb);
  mode_t p = sb.st_mode;
  int other = p % 8;
  p = p / 8;
  int group = p % 8;
  p = p / 8;
  int user = p % 8;
  char* u = get_permissions(user);
  char* g = get_permissions(group);
  char* o = get_permissions(other);
  printf("Readable permissions: %s%s%s\n",u,g,o);
}

int main(){
  //Creating a test file
  int r = open("test_file",O_CREAT|O_WRONLY,0666);
  printf("\nTest file successfully created\n");
  char* s = "Hello";
  write(r,s, sizeof(s));
  close(r);

  return_size("test_file");
  return_mode("test_file");
  return_time("test_file");
  readable_size("test_file");
  readable_permissions("test_file");

}
