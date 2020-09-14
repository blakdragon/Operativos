#include "utils.h"

int main(int args_count, char *args_vector[]){
	if(args_count < 2){
		printf("Se debe llamar con un argumento\n");
		return 0;
	}
	
	char string_to_produce[3];
	strcpy(string_to_produce, args_vector[1]);	

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
    
    for(int i = 0; i < 100; i ++){
    	sem_wait(shared_memory_semaphore);

    	int idx = shared_memory -> write_count;
    	strcpy(shared_memory -> content[idx], string_to_produce);
    	shared_memory -> write_count++;
    	printf(
    		"Proceso %d produciendo %s en indice %d\n",
    		getpid(),
    		string_to_produce,
    		idx
    	);

    	sem_post(shared_memory_semaphore);
    	sem_post(empty_semaphore);        	
    }

    detachSharedMemory(shared_memory);        

	return 0;
}