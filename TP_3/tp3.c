#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

#define TAILLE 1024
#define KEY 1234

void ecrire_tableau(int *compteur, char *tableau) {
  char message[64], *msg=message;
  snprintf(message, 64, "Je suis le processus %d!\n", getpid());

  while ((*compteur<TAILLE)&&(*msg)) {
    tableau[*compteur] = *msg;
    msg++;
    usleep(100000);
    (*compteur)++;
  }
}

struct sembuf down = { 0, -1, 0}; // Entree dans la zone critique 
struct sembuf up = { 0, +1, 0}; // Sortie de la zone critique 
int semId;

int main() {

  // Creation du semaphore 
  semId = semget(KEY, 1, 0600 | IPC_CREAT | IPC_EXCL) ; 

  if (semId >= 0) // Si il n'existe pas encore 
  {
    semop(semId, &up, 1); 

     printf("Creation du semaphore :\t%d\n",semId) ;
  }
   
    //Entrée dans la zone mémoire

    semId = semget(KEY, 1, 0600 | IPC_CREAT ) ;

    if (semop(semId, &down, 1) < 0)
    {
      perror("semop down"); exit(13);
    }

    else
    {
        int id, *compteur;
        char *tableau;

        id = shmget((key_t)KEY,TAILLE+sizeof(int),0600|IPC_CREAT); // Création d'un nouveau segment de mémoire partagée
        if (id<0) { perror("Error shmget"); exit(1); }

        compteur = (int*) shmat(id,0,0);  // Debut de l'utilisation du segment de mémoire partagée 
        if (compteur==NULL) { perror("Error shmat"); exit(1); }

        tableau = (char *)(compteur + 1);
        
        ecrire_tableau(compteur, tableau);
        printf("%s\n", tableau);

        if (shmdt(compteur)<0) { perror("Error shmdt"); exit(1); } // Détacher du segment  mémoire 

          // Sortie de la zone critique 
         if(semop(semId, &up, 1) < 0)
            {
                perror("semop up"); exit(14);
            } 
    }
  return 0;
}

