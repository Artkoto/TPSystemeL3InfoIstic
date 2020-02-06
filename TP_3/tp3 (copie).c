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

int main() { 

  int id, *compteur;
  char *tableau; 
  int semId; 
  int semOp;

  struct sembuf up = {0,1,0};
  struct sembuf down = {0,-1,0};

  id = shmget((key_t)KEY,TAILLE+sizeof(int),0600|IPC_CREAT); // Crée la mémoire partagée avec un nouveau segment
  if (id<0) { perror("Error shmget"); exit(1); } 

  semId = semget((key_t)KEY, 1, 0600); // Déclaration du tableau de sémaphores 
  if (semId == -1){perror("Erreur de déclaration"); exit(1);}

  compteur = (int*) shmat(id,0,0); // Utilser un segment de mémoire partagée 
  if (compteur==NULL) { perror("Error shmat"); exit(1); } 

  semOp = semop(semId, &down, 1); // Entrée et blocage de la zone critique 
  if (semOp == -1){perror("Erreur d'entrée dans le sémaphore "); exit(1);}

  tableau = (char *)(compteur + 1);
  
  ecrire_tableau(compteur, tableau);
  printf("%s\n", tableau);

  semOp = semop(semId, &up, 1); // libération de la zone critique 
  if (semOp == -1){perror("Erreur d'entrée dans le sémaphore "); exit(1);}

  if (shmdt(compteur)<0) { perror("Error shmdt"); exit(1); } // Détacher le segment  mémoire de la clé
  return 0;

}

