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
  int size = sb.st_size;
  printf("File size: %d \n", size);
}

void return_mode(char *file){
  struct stat sb;
  stat(file, &sb);
  int permissions = sb.st_mode;
  printf("File permissions: %o \n", permissions);
}

void return_time(char *file){
  struct stat sb;
  stat(file, &sb);
  char *last_access = ctime(&sb.st_atime);
  printf("File permissions: %s \n", last_access);
}

int main(){
  //Creating a test file
  int r = open("test_file",O_CREAT|O_WRONLY,0666);
  printf("\nTest file successfully created\n");
  write(r,"Hello", sizeof("Hello"));
  close(r);

  return_size("test_file");
  return_mode("test_file");
  return_time("test_file");
}
