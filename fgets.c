#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 80

int main(int argc, char *argv[]) 
{
	char cmd[MAX_LINE];

	/* Get user input */
	fgets(cmd, MAX_LINE, stdin);
	printf("The input was [%s]\n",cmd);
	
	return 0;
}
