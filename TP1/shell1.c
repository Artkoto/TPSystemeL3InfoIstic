#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include <stdbool.h>
#include<signal.h>

int main(int argc, char const *argv[])
{
    
    int SIZE_MAX = 20; //taille max des commandes
    char nomDeLaCommande [SIZE_MAX]  ;
    char PATH [] = "/bin/"; 
    bool stop = false ;

   
    while (!stop)
    {
        printf ("Entrez la commande ici :");
       // scanf("%s", nomDeLaCommande);
       fgets(nomDeLaCommande , SIZE_MAX , stdin);
       //on remplce le \n par \0 ce qui à pour effet de supprimer le retour à la ligne
       nomDeLaCommande[(strlen(nomDeLaCommande) - 1)] = '\0';
       
        printf ("Commande : %s \n",nomDeLaCommande);
        pid_t pid_fils ;
        

        if (strcmp (nomDeLaCommande, "exit") == 0 )
        {
            //fermeture du shell si on tape la commande exite
           stop = true;
           printf ("Fermeture du shell \n");
           exit(0);
        }        

        else{
            switch (pid_fils = fork()){

            case 0 : execl( strcat(PATH, nomDeLaCommande),nomDeLaCommande , NULL);
                    fprintf(stderr, "impossible d'executer la commande\n");
                    kill(getpid(),SIGKILL);
                    break;

            case -1 : perror("erreur defork");
                     exit(1) ;
                    break;

            default :
                    
                    waitpid(-1,NULL,0);
                   
                    break;
        }
        }
    }

    return 0;
}
