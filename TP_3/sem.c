#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

#define TAILLE 1024
#define KEY 1234

int main()
{
    
    int id = shmget((key_t)KEY,TAILLE+sizeof(int),0600|IPC_CREAT);
    int semId; 

    //struct sembuf down = { 0, -1, 0}; // attente
    struct sembuf up = { 0, +1, 0}; // le execution 

    semId = semget((key_t)KEY, 1, 0600|IPC_CREAT |IPC_EXCL);
    if (semId != -1)
    {
            semop(semId, &up, 1);

     printf("création du semaphore :\t%d \t%d\n",semId ,id);
    }

    else
    {
        printf("le semaphore existe deja\n");
    }
    
    


    return 0;
}

