#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>

#ifndef MAX_CANON
#define MAX_CANON 8192
#endif

int makeargv(char *s, char * delimiters, char ***argvp);
FILE *input;


int main (int argc, char * argv[]){
	
	char delim[] = " ";
	char *argstr;
	char **cmd;	
	int tokennum;

	if (argc != 2){
		printf("too many arguments");
		return -1;
	}
	int pr_limit = atoi(argv[1]);
	printf("pr_limit: %d\n", pr_limit);
	
	char * line = malloc(MAX_CANON);
	input = fopen("testing.data", "r");
	while (fgets(line, MAX_CANON, input) != NULL) {
		if((tokennum = makeargv(line, delim, &cmd)) != -1){
			printf("%s %s", cmd[0], cmd[1]);
			execvp(cmd[0], &cmd[0]);
		}
		
		//printf("%s",line);
	}
	free(line);
	fclose(input);


	

	



		

return 0;
}
