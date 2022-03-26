#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct {
    int cote[2];
} t_pipe;

void processus(int n, t_pipe tabPipe[])
{
    size_t i;
    for (i=0; i < n; i++)
    {
        if ((i + 1) != n){
            close(tabPipe[0]);
        }
        if (i != n)
        {
            close(tabPipe[1]);
        }
    }
}

void listePid(int PID, int tabPid,int *i){
    tabPid[&i] = PID;
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);  // Nb de processus
    int m = atoi(argv[2]);  // Nb de tour
    int jeton = m;          // Création du jeton avec le nombre de tour

    t_pipe tableaupipe[] = (t_pipe*)malloc(n*sizeof(t_pipe));
    int tabPid[] = (int*)malloc(n*sizeof(t_pipe));

    // Création des tubes
    for(int i=0; i<n; i++)
    {
        pipe(&tableaupipe[i]);
    
        if (&tableaupipe[i] == -1)
        {
            fprintf(stderr, "Erreur ouverture pipe\n");
            exit(1);
        }
    }

    // Création des répertoire
        for(int i=0; i<n; i++)
    {
        if(fwork()==1)
        {
            printf("%d",getpid());

            char *nomRep = getpid();
            mkdir(nomRep, S_IRWXU);
            listePid(getpid(),tabPid,i);
            wait(NULL);
            sleep(NULL);
            exit(0);
        }
    }

    //Affichage du tableau de tabPid
    printf("Tableau de PID : \n");
    for(int i=0; i<n; i++){
        printf("%d \t",tabPid[i]);
    }
}