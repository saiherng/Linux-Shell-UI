#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define ARGV_SIZE 10

int main(int argc, char *argv[]) {
  char *myArgv[ARGV_SIZE];  // an array of pointers to strings

  myArgv[0] = "ps";
  myArgv[1] = "-aux";
  myArgv[2] = NULL;  // last element should be a NULL pointer

  execvp(myArgv[0], myArgv);
  return 0; // should not be reached