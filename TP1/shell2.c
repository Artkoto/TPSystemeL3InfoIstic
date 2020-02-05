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
            char *instruction ;
            char *param [SIZE_MAX];
            char temp [SIZE_MAX][SIZE_MAX];
            char chaine [SIZE_MAX];
            char PATH [] = "/bin/"; 
            bool stop = false ;

  
    while (!stop)
    {
            
        printf ("Entrez la commande ici :");
       // scanf("%s", nomDeLaCommande);
       fgets(chaine , SIZE_MAX , stdin);
        
        instruction = strtok(chaine , " ");
         strcpy(nomDeLaCommande , instruction);
       //on remplce le \n par \0 ce qui à pour effet de supprimer le retour à la ligne
       char f1 =nomDeLaCommande[(strlen(nomDeLaCommande) - 1)];
        nomDeLaCommande[(strlen(nomDeLaCommande) - 1)] = (f1 == '\n')?'\0':f1;

        
        int i = 0; //le nombre d'arguments de l'instruction
        while (instruction != NULL)
        {
            
            strcpy(temp[i],instruction);
            instruction =  strtok(NULL , " ");
           //on remplce le \n par \0 ce qui à pour effet de supprimer le retour à la ligne
           char f2 =temp[i][(strlen(temp[i]) - 1)];
           temp[i][(strlen(temp[i]) - 1)] = (f2 == '\n')?'\0':f2;

           //on ne prend pas le carectere d'echapement en compte
            if (strcmp (temp[i], "\0") != 0 && strcmp (temp[i], "") !=0 )
            {
                *(param+i) = *(temp+i);
                 ++i;
            }
 
        }
         *(param+i) = NULL;


        printf ("> %s\n",nomDeLaCommande);

        pid_t pid_fils ;
        

        if (strcmp (nomDeLaCommande, "exit") == 0 )
        {
            //fermeture du shell si on tape la commande exite
           stop = true;
           printf ("Fermeture du shell \n");
         
        }        

        else{
            switch (pid_fils = fork()){

            case 0 : execv( strcat(PATH, nomDeLaCommande),(param));
                    fprintf(stderr, "impossible d'executer la commande\n");
                    kill(getpid(),SIGKILL);
                    break;

            case -1 : perror("erreur de fork");
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
