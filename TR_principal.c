#include <stdio.h>

typedef struct {
    int cote[2];
} t_pipe;


int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);  // Nb de processus
    int m = atoi(argv[2]);  // Nb de tour
    int jeton = m;          // Création du jeton avec le nombre de tour

    t_pipe tableaupipe[] = (t_pipe*)malloc(n*sizeof(t_pipe));

    for(int i=0; i<n; i++)
    {
        pipe(&tableaupipe[i]);
    
        if (&tableaupipe[i] == -1)
        {
            fprintf(stderr, "Erreur ouverture pipe\n");
            exit(1);
        }
    }
}