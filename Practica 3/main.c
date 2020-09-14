#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#include "utils.h"


int main(int args_count, char *args_vector[]){

	if(fork() == 0){
		char *child_args[] = {"./producer", "aa", NULL};
		execv(child_args[0], child_args);
	}
	if(fork() == 0){
		char *child_args[] = {"./producer", "bb", NULL};
		execv(child_args[0], child_args);
	}
	if(fork() == 0){
		char *child_args[] = {"./producer", "cc", NULL};
		execv(child_args[0], child_args);
	}
	if(fork() == 0){
		char *child_args[] = {"./producer", "dd", NULL};
		execv(child_args[0], child_args);
	}
	
	if(fork() == 0){
		char *child_args[] = {"./consumer", NULL};
		execv(child_args[0], child_args);	
	}

	if(fork() == 0){
		char *child_args[] = {"./consumer", NULL};
		execv(child_args[0], child_args);	
	}

	if(fork() == 0){
		char *child_args[] = {"./consumer", NULL};
		execv(child_args[0], child_args);	
	}

	int status;
	for(int i = 0; i < 7; i++)
		wait(&status);

	clear();

	return 0;
}