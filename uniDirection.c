#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Nombre total de thread
#define NB_FORK 2
// Taille du message
#define LENGTH_MSG 30
// Tableau contenant le message
char message[LENGTH_MSG] = "";

// Fonction exécutée dans le fork
void job(int * tube, int NB) {
	int tid = getpid();
	// timer pour attendre maximum 5 secondes
	int i = 5;
	while (i > 0) {
		// lecture dans le tube
		if (read(*tube, message, LENGTH_MSG) > 0) {
			printf("Message du processus [%i] : %s", tid, message);
			break;
		}
		sleep(1);
	}
}
// Fonction qui attend chacun des processus fils
void waitForAll(int NB) {
	int status;
	pid_t pid;
	int n = 0;
	while (n < NB) {
		pid = wait(&status);
		n++;
	}
}

int main(int argc, char *argv[]) {
    int NB = atoi(argv[1]);

	for (int i = 0; i < NB; i++) {
		int tube[2];
		pipe(tube);
		pid_t pid = fork();
		if (pid == -1) {
			// Il y a une erreur
			perror("fork");
			return EXIT_FAILURE;
		} else if (pid == 0) {
			// On est dans le fils
			close(tube[1]);
			job(&tube[0],NB);
			close(tube[0]);
			exit(EXIT_SUCCESS);
		} else {
			// On est dans le père
			// Ecriture du message dans le tableau
			sprintf(message, "Fork [%i], je suis ton père !\n", pid);
			// Ecriture du message dans le tube
			write(tube[1], message, LENGTH_MSG);
			close(tube[0]);
			close(tube[1]);
		}
	}
	waitForAll(NB);
	return EXIT_SUCCESS;
}