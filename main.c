#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char * argv[]){

	printf("Hello World\n");

	pid_t childpid = 0;
	int i,n;
	int opt;

	while((opt = getopt(argc, argv, "hn:")) != -1){
		switch (opt){
			case 'h':
				printf("Help text");
				return -1;
			case 'n':
				printf("Do Work");
				break;
			default:
				perror(argv[0]);
				break;
		}
	}
	
	/*if (argc != 2){
		perror(argv[0]);
		return(-1);
	}*/
	
	n= atoi(argv[2]);
	for (i = 1; i <n; i++) {
		if ((childpid = fork()) <= 0)
			break;
	}

	fprintf(stderr, "i:%d process ID: %ld parent ID:%ld child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);

return 0;
}
