#include "system.h"
#include "TubeManager.h"
#include "FileManager.h"
#include <signal.h>

TubeManager *tm_arr = NULL;
bool quit = false, toggle = true;
int proc_c = 0, jump_c = 0;

void handler(int sig) {
    int i;
    switch(sig) {
        case SIGQUIT:
            signal(SIGQUIT, handler);
            quit = true;
            break;
        case SIGUSR1:
            signal(SIGUSR1, handler);
            if(tm_arr != NULL) {
                toggle = !toggle;
                if(toggle) {
                    for(i=0; i<proc_c; i++) {
                        kill(tm_arr[i].proc, SIGCONT);
                    }
                    printf("Continuer\n");
                } else {
                    for(i=0; i<proc_c; i++) {
                        kill(tm_arr[i].proc, SIGSTOP);
                    }
                    printf("Stopper\n");
                }
            }
            break;
    }
}

int main(int argc, char *argv[]) {
    int token, move, i;
    pid_t pid;
    stream_t **ts = NULL;
    TubeManager *M = NULL;
    struct timespec time;
    int old_ms = 0, cur_ms = 0;

    if(argc != 3) {
        printf("Nombre d'arguments incorrect\n");
        die();
    }
    proc_c = atoi(argv[1]);
    jump_c = atoi(argv[2]);
    if(proc_c <= 0 || jump_c <= proc_c) {
        printf("Valeur(s) du (des) paramètre(s) incorrecte(s)\n");
        die();
    }
    tm_arr = (TubeManager*) malloc(proc_c*sizeof(TubeManager));
    if(tm_arr == NULL) {
        printf("Erreur d'allocation dynamique\n");
        die();
    }
    ts = tubes(proc_c);
    if(ts == NULL) {
        printf("Erreur d'allocation dynamique\n");
        die();
    }

    signal(SIGQUIT, handler);
    signal(SIGUSR1, handler);
    printf("Processus pere (pid: %d) en cours d'execution...\n", getpid());
    printf("\t> Tapez 'kill -s usr1 %d' pour stopper/continuer l'execution des processus fils\n", getpid());
    printf("\t> Tapez 'kill -s quit %d' pour quitter le processus père\n", getpid());
    printf("======================================================================\n\n");

    clock_gettime(CLOCK_REALTIME, &time);
    old_ms = time.tv_nsec / 1000;

    for(i=0; i<proc_c; i++) {
        createTubeManager(&tm_arr[i], ts, proc_c, i);
        createDir(i);
        if((pid = fork()) == 0) {
            M = &tm_arr[i];
            M->proc = getpid();
            closeTubes(ts, proc_c, M);

            if(i == 0) {
                token = jump_c;
                write(M->write, &token, sizeof(int));
            }
            do {
                read(M->read, &token, sizeof(int));
                token--;
                move = jump_c - token;
                if(token >= 0 && dirExist(i)) {
                    clock_gettime(CLOCK_REALTIME, &time);
                    cur_ms = time.tv_nsec / 1000;
                    editTime(i, move, cur_ms, old_ms);
                    old_ms = cur_ms;
                }
                write(M->write, &token, sizeof(int));
            } while(token > 0);
            printf("Fin du processus fils no.%d, pid: %d, token: %d \n", i, M->proc, token);

            freeTubes(ts, proc_c);
            end();
        }
        tm_arr[i].proc = pid;
    }
    while(!quit);
    printf("Terminaison du programme\n");
    closeTubes(ts, proc_c, NULL);
    freeTubes(ts, proc_c);
    free(tm_arr);
    tm_arr = NULL;
    end();
}
