#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include <stdbool.h>
#include<signal.h>


                //////////////////////////////////////////////////
                ///             saisie au clavier            ////
                ////////////////////////////////////////////////

void saisieAuClavier (char commande[] , char *prm[]){

        int SIZE_MAX = 256; //taille max des commandes
        char *instruction ;
        char temp [SIZE_MAX][SIZE_MAX];
        char chaine [SIZE_MAX];

        printf ("> :");
       // scanf("%s", commande);
       fgets(chaine , SIZE_MAX , stdin);
        
        instruction = strtok(chaine , " ");
         strcpy(commande , instruction);
       //on remplce le \n par \0 ce qui à pour effet de supprimer le retour à la ligne
       char f1 = commande[(strlen(commande) - 1)];
        commande[(strlen(commande) - 1)] = (f1 == '\n')?'\0':f1;

        
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
                *(prm+i) = *(temp+i);
               // puts(*(prm+i));
                 ++i;
            }
 
        }
         *(prm+i) = NULL;

}

                //////////////////////////////////////////////////
                //    verification de la condition d'arret   ////
                ////////////////////////////////////////////////

void conditionExit( char commande[]){

         if (strcmp (commande, "exit") == 0 )
                {
                //fermeture du shell si on tape la commande exite
                printf ("Fermeture du shell \n");
                exit(0);
                } //
}


                //////////////////////////////////////////////////
                //                   LE MAIN                 ////
                ////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
    
            int SIZE_MAX = 256; //taille max des commandes
            char nomDeLaCommande [SIZE_MAX];
            char nomDeLaCommande2 [SIZE_MAX] ;
            char *param [SIZE_MAX];
            char *param2 [SIZE_MAX];
            char PATH [] = "/bin/"; 
            bool stop = false ;
            int tube [2];
           

  
    while (!stop)
    {
        fprintf(stdout,"\ncommande 1 :");
        saisieAuClavier(nomDeLaCommande , param);
        conditionExit(nomDeLaCommande);

        pid_t pid_fils ;
        
            if (pipe(tube) != 0)
            {
                perror("erreur de pipe");
                     exit(1) ;
            }

            else
            {

                fprintf(stdout,"commande 2 :");
                saisieAuClavier(nomDeLaCommande2 , param2);
                conditionExit(nomDeLaCommande2);

                    switch (pid_fils = fork()){

                    case 0 : {
                        dup2(tube[1],STDOUT_FILENO);
                         close(tube[0]);
                         close(tube[1]);
                        execv( strcat(PATH, nomDeLaCommande),param);
                        kill(getpid(),SIGKILL);
                        break;
                            }

                    case -1 : perror("erreur de fork");
                            exit(1) ;
                            break;

                    default :
                            
                        waitpid(-1,NULL,0);

 ///////////////////////////// 2eme fils //////////////////////////////////////
                     switch (pid_fils = fork()){

                    case 0 : 
                    dup2(tube[0],STDIN_FILENO);
                    close(tube[0]);
                    close(tube[1]);
                    execv( strcat(PATH, nomDeLaCommande2),param2);
                    kill(getpid(),SIGKILL);
                    break;

                    case -1 : perror("erreur de fork");
                            exit(1) ;
                            break;

                    default :
                            close(tube[0]);
                           close(tube[1]);
                            waitpid(-1,NULL,0);

                            
                        
                            break;
                     }
 //////////////////////////////////////////////////////////////////////                       
                    break;
                }
        }
        
    }

    return 0;
}
