#include "utils.h"

int main(int args_count, char *args_vector[]){
	int shared_memory_id = getSharedMemory(
        SHARED_MEMORY_KEY,
        sizeof(SharedMemory),
        USER_AND_GROUP|IPC_CREAT
    );
    SharedMemory *shared_memory = attachSharedMemory(
        shared_memory_id,
        NULL,
        NO_FLAGS
    );
       
    sem_t *shared_memory_semaphore = sem_open(
    	SHARED_MEMORY_OCCUPIED,
    	O_CREAT,
    	USER_AND_GROUP,
    	1
    );
	sem_t *empty_semaphore = sem_open(
    	EMPTY,
    	O_CREAT,
    	USER_AND_GROUP,
    	0
    );
    
    while(TRUE){    	
    	sem_wait(empty_semaphore);
    	sem_wait(shared_memory_semaphore);

    	int idx;
    	idx = shared_memory -> read_count;    	
    	shared_memory -> read_count++;
    	printf(
    		"Proceso %d consumiendo %s de indice %d\n",
    		getpid(),
    		shared_memory -> content[idx],
    		idx
    	);

    	sem_post(shared_memory_semaphore);

    	if(idx >= TOTAL_TO_PRODUCE - 3)
    		break;
    }

    detachSharedMemory(shared_memory);

	return 0;
}