#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#ifndef MAX_CANON
#define MAX_CANON 8192
#endif

int makeargv(char *s, char * delimiters, char ***argvp); //using provided makeargv.c function from MHauschild
FILE *input;
int pr_limit;
int pr_count = 0;

int main (int argc, char * argv[]){

	int opt;

	//the getopt loop is based on a loop found on www.gnu.org for using getopt
	while((opt = getopt(argc, argv, "hn:")) != -1){ //getoptions from command line 
		switch (opt){
			case 'h':
				printf("Help text");
				printf("\nUsage: ./exe [option] [max_processes] ./[file]\n");
				return -1;
			case 'n':
				break;
			case '?':
				printf("Usage: ./exe [option] [max_processes] ./[file]\n");
				//perror(argv[0]);
				return -1;
			default:
				return -1;
		}
	}

	char delim[] = " ";
	char *argstr = malloc(MAX_CANON);
	char **cmd;
	int tokennum;

	pid_t childpid = 0;
	pid_t waitreturn;
	int i;
	int j;
	
	//pulled/edited from Exercise 3.2 in Robbins book
	pr_limit = atoi(argv[2]);
	input = fopen(argv[3], "r");
	if (input == NULL){
		perror(argv[0]);
		return -1;
	}

	while(fgets(argstr, MAX_CANON, input) != NULL){ //read lines from file
		if(pr_count < pr_limit){
			childpid = fork(); //if process count is under limit and fork is successful
			printf("\nchild process created %ld, parent: %ld, child: %ld\n", (long)getpid(), (long)getppid(), (long)childpid);
			pr_count++; //incr process count
			printf("pr_count after fork: %d\n", pr_count);
			if((tokennum = makeargv(argstr, delim, &cmd)) != -1){ //check arg is valid and run command
				execvp(cmd[0], &cmd[0]);
				break;
			}
		}
		else if (pr_count == pr_limit){
			printf("process limit reached. Waiting..\n");
			while (childpid != (waitreturn = wait(NULL))){
				if ((waitreturn == -1 && errno != EINTR)){
					break;
				}
			}
		}	
	}
	printf("\nchild process executed\n");
	

	 
	/*for (i = 1; i <pr_limit; i++) {
		printf("i=%d \n", i);
		
		if ((childpid = fork())){
			printf("In Child process (pid: %d)\n", getpid());
			break;
		}
	}
	while (childpid != (waitreturn = wait(NULL))){
		if ((waitreturn == -1 && errno != EINTR)){
			break;
		}
	}
	*/


	//fprintf(stderr, "i:%d process ID: %ld parent ID:%ld child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);

return 0;
}
