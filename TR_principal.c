#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>


typedef struct t_pipe{
    int cote[2];
} t_pipe;



void ajoutPID(int pid, int i, int tabGID[])
{
    printf("%d\n", pid);
    tabGID[i] = pid;

    printf("Liste des PID :  \n");
    for (int i = 1; i <= 3; i++)
    {
        printf("%d \t",tabGID[i]);
    }
    printf("\n");

}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);  // Nb de processus
    int m = atoi(argv[2]);  // Nb de tour
    int jeton = m;          // Création du jeton avec le nombre de tour

    int *tabGID = (int*)malloc(n*sizeof(int));
    
    if (tabGID == NULL)
    {
        printf("Echec de l'allocation \n");
        return EXIT_FAILURE;
    }

    //Création des processus
   for (int i = 1; i <= n; i++)
    {   
        if(fork()==0){
            int pid = getpid();
            printf("Numero du processus : %d sur %d | Numéro GID : %d \n", i, n, pid);
            ajoutPID(pid,i,tabGID);
            wait(NULL);
            exit(0);
        } 
        wait(NULL);
    }

    //Création des tubes
    
    exit(0);

}