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

struct sembuf down = { 0, -1, 0}; // attente
struct sembuf up = { 0, +1, 0}; //  execution du suivant
int semId;

int main() {

  //int sémaphore
  semId = semget(KEY, 1, 0600 | IPC_CREAT);

  if (semId < 0)
  {
    perror("Erreur de déclaration de semaphore"); exit(11);
  }

  else
  {
    //Entrer dans la zone mémoire
    if (semop(semId, &down, 1) < 0)
    {
      perror("semop down"); exit(13);
    }
    else
    {
        int id, *compteur;
        char *tableau;

        id = shmget((key_t)KEY,TAILLE+sizeof(int),0600|IPC_CREAT);// Crée la mémoire partagée avec un nouveau segment
        if (id<0) { perror("Error shmget"); exit(1); }

        compteur = (int*) shmat(id,0,0);  // Utilser un segment de mémoire partagée 
        if (compteur==NULL) { perror("Error shmat"); exit(1); }

        tableau = (char *)(compteur + 1);
        
        ecrire_tableau(compteur, tableau);
        printf("%s\n", tableau);

        if (shmdt(compteur)<0) { perror("Error shmdt"); exit(1); } // Détacher le segment  mémoire de la clé

          //liberation de la zone mémoire
         if(semop(semId, &up, 1) < 0)
            {
                perror("semop up"); exit(14);
            }

        return 0;
    }
  }
}

