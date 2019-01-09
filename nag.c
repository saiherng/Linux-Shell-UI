#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define ARGV_SIZE 10


int main() {

  char *myArgv[ARGV_SIZE];
  pid_t pid;
  myArgv[0] = "ps";
  myArgv[1] = "-aux";
  myArgv[2] = NULL;

  int i =0;

  if ((pid = fork()) == 0) {
    while (i<10) {
      printf("child's return value %d:  I want to play…\n", pid);
      execvp(myArgv[0], myArgv);
      i++;
      
    }
  } else {
    while (1) {
      printf("parent's return value %d:  After the project…\n", pid);
    }
  }
  return 0;
}
