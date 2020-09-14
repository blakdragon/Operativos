#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 

#define getSharedMemory shmget
#define attachSharedMemory shmat
#define detachSharedMemory shmdt
#define sharedMemoryControl shmctl

#define TRUE 1
#define NO_FLAGS 0
#define USER_AND_GROUP 0660
#define SHARED_MEMORY_KEY 0x2468
#define SHARED_COUNTER_KEY 0x8642

#define SHARED_MEMORY_OCCUPIED "/semaphore-shared-memory-occupied"
#define EMPTY "/semphore-empty"

const int TOTAL_TO_PRODUCE = 400;

typedef struct SharedMemory{
    char content[400][3];
    int write_count;
    int read_count;
} SharedMemory;

void clear(){
	int shared_memory_id = getSharedMemory(
        SHARED_MEMORY_KEY,
        sizeof(SharedMemory),
        USER_AND_GROUP|IPC_CREAT
    );
    sharedMemoryControl(
        shared_memory_id,
        IPC_RMID,
        NULL
    );
    sem_unlink(SHARED_MEMORY_OCCUPIED);
    sem_unlink(EMPTY);
}