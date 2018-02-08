#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main (int argc, char * argv[]){

	if (argc != 3){
		printf ("check arguments");
		return -1;
	}

	int i;
	int sleepTime = atoi(argv[1]);
	int loopIter = atoi(argv[2]);

	for (i = 1; i <= loopIter; i++){
		sleep(sleepTime);
		printf("slept for %d\n", sleepTime);
	}
return 0;
}
