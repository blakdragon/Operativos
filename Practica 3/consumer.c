#include "utils.h"

int main(int args_count, char *args_vector[]){
    SharedMemory *shared_memory;
    sem_t *shared_memory_semaphore, *empty_semaphore;
    init(
        &shared_memory,
        &shared_memory_semaphore,
        &empty_semaphore
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