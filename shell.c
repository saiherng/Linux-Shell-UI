/********************************************************************
* Name of Program: shell.c
* Authors: Sai Herng
* Description: This program is run with ./shell:
              * Part 0: Create the structure of the shell.
              * Part 1: Taking input from the user.
              * Part 2: Change user input to tokens.
              * Part 3: Executes user input commands via tokens.
              * Part 4: Implmenting built-in commands to our shell.
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MAX_LINE 80
#define ARGV_SIZE 10


char userInput[MAX_LINE];
const char delim[2] = " ";
char * token;
char cmd[10][MAX_LINE];
char * myArgv[ARGV_SIZE];


int i, w, p; // counters

int status;
pid_t pid, wpid;

int processes[5]; // process list
char cwd[1000]; // directory array

int main(int argc, char* argv[] ){


  while(1){

    //gets current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL){
      printf(ANSI_COLOR_GREEN "%s : " ANSI_COLOR_RESET, cwd);
    }
    fgets(userInput, MAX_LINE, stdin);
    userInput[strlen(userInput)-1] = '\0';

    //breaks if quit is tpyed
    if (strcmp(userInput,"quit")==0){
      printf(ANSI_COLOR_RED "exit\n" ANSI_COLOR_RESET );
      return 0;
    }

    //  get the first token
    token = strtok(userInput, delim);

    i = 0, w = 0; // resetting counter

    //get other tokens
    while( token != NULL ) {
      strcpy(cmd[i], token);
      token = strtok(NULL, delim);
      i++;
      w++; // count tokens
    }

    //
    for (i=0; i < w; i++){
      myArgv[i] = cmd[i];
    }
    myArgv[w] = NULL;

    // checks if input is a built-in function
    if (strcmp(myArgv[0],"showpid") == 0) {
      // printing latest 5 processes
      for (i=0; i< 5; i++){
        if (processes[i] != 0){
          printf("%d\n", processes[i]);
        }
      }
    }

    else if (strcmp(myArgv[0], "cd") == 0) {
      chdir(myArgv[1]); // directs to path
    }

    else{
      pid = fork();
      if (pid == 0) {
        // Child process
        if (execvp(myArgv[0], myArgv) == -1) {
          fprintf(stderr, "Error: Command could not be executed\n");
        }
        exit(EXIT_FAILURE);
      }

      else if (pid < 0) {
        // Error forking
        fprintf(stderr, "Error: Command could not be executed\n");
      }

      else {
        // Parent process
        do {
          wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        // creates list of latest processes
        if (p == 5) {
          p = 0; //resetting index to update latest process
        }
        processes[p] = pid; //appends process to list
        p++; // incremeting list index for process

      }
    }
  }
}
