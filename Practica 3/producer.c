#include "utils.h"

int main(int args_count, char *args_vector[]){
	if(args_count < 2){
		printf("Se debe llamar con un argumento\n");
		return 0;
	}
	
	char string_to_produce[3];
	strcpy(string_to_produce, args_vector[1]);	

	SharedMemory *shared_memory;
    sem_t *shared_memory_semaphore, *empty_semaphore;
    init(
        &shared_memory,
        &shared_memory_semaphore,
        &empty_semaphore
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