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


int main() {

    int id = shmget((key_t)KEY,TAILLE+sizeof(int),0600|IPC_CREAT);
    int semId = semget((key_t)KEY, 1, 0600|IPC_CREAT); // Déclaration du tableau de sémaphores 
    shmctl(id, IPC_RMID, 0);
    printf("Segment de mémoire %d détruit.\n", KEY);
    semctl(semId, 0, IPC_RMID);  
    printf("Semaphore %d détruit.\n", semId);

}