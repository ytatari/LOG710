#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>

/***************************************************************
 *	Titre:			RunCmd
 *
 *	Description:	Troisième partie du laboratoire.
 *					Execution d'une commande pour accéder à
 *					un interpréteur de commande shell pour 
 *					finalement afficher des statistiques 
 *					relatives a l'execution.
 *					Execution d'une commande en arrière plan.
 *			
 *		
 *	Etudiants:		Alexandre Laroche
 *					Tiahiti Caspar
 *
 *	Cours:			LOG710
 *	Institution:	ETS
 *	
 *	Date:			02 octobre 2018
 *
 ***************************************************************/

typedef struct
{
	int _task;
	int _pid;
	char _cmd[];
} Commande;

Commande cmd[100];

int i;
pid_t pid;
char *arg[5];
int task = 1;
char *str[60];
int retourTraitement = 0;
int positionAjoutTache = 0;
struct timeval timeOfDayStart;

/***************************************************************
 *					Handler - Gestion des signaux
 ***************************************************************/
void handler(int sig)
{
	int pid;

	switch(sig)
	{
		case SIGUSR1:break;
		
		case SIGUSR2:break;
		
		case SIGCHLD:
			pid = wait(NULL);
			int positionRetraitTache = 0;
			for (positionRetraitTache; positionRetraitTache < 100; positionRetraitTache++) {
				if (cmd[positionRetraitTache]._pid == pid) {
					cmd[positionRetraitTache - 1]._task = NULL;
					cmd[positionRetraitTache]._pid = NULL;
					positionRetraitTache = positionRetraitTache + 2;
					break;
				}	
			} 
			break;
			
		default:break;
	}
}

/***************************************************************
 *					MAIN - Demarrer l'execution
 ***************************************************************/
int main(int argc, char* argv[])
{
	int etat;
	
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset (&action.sa_mask);
	action.sa_flags = 0;

	if(sigaction(SIGUSR1,&action,NULL) < 0)
		printf("Erreur de traitement de code de l'action\n");
	if(sigaction(SIGUSR2,&action,NULL) < 0)
		printf("Erreur de traitement de code de l'action\n");
	if(sigaction(SIGCHLD,&action,NULL) < 0)
		printf("Erreur de traitement de code de l'action\n");

	do {
		
		printf("Log710Shell%>");
		int retourTraitement = traitementEntree(); 
		
		if (retourTraitement == 1)
		{
			if(strcmp(arg[0], "exit") == 0){
				int p = 0;
				bool sortie = 1;
				do {
					if (cmd[p]._task < 30 && cmd[p]._task != 0) {
						printf("Processus en cours ...\n");
						sortie = 0;
					}
					p = p + 3;
				} while (p < 100);

				if (sortie == 1) exit(0);				
			} 
			else if (strcmp(arg[0], "cd") == 0) {
				chdir(arg[1]);	
			}	
			else if(strcmp(arg[0], "ap") == 0) {
				int p = 0;
				do {
					if (cmd[p]._task < 30 && cmd[p]._task != 0) {
						printf("[%d] %d %s\n", cmd[p]._task, cmd[p+1]._pid, cmd[p+2]._cmd);
					}
					p = p + 3;
				} while (p < 100);
			}
			else {

				pid = fork(); 

				if( pid == 0)
				{
					//printf("Le pid du fils : %d et le père : %d\n", getpid(), getppid());	
					kill(getppid(),SIGUSR2);

					if (strcmp(arg[i - 1], "&") != 0){
						retourTraitement = 0;
						execvp(arg[0], arg);
					}
					else {
						arg[i - 1] = NULL;
						//Simulation d'une commande en arrière plan
						//sleep(10);
						execvp(arg[0], arg);
					}
					printf("Erreur d'exécution\n");
					abort();
					exit(1);
				} 
				else if (pid > 0)
				{
					//printf("Le pid du père : %d et le fils : %d\n", getpid(), pid);
					kill(pid,SIGUSR1);
					
					if (strcmp(arg[i - 1], "&") != 0) {
						pause();
						int rUsage = 1;
						int wallClockTime = 1;
						struct rusage usage;
						struct timeval timeOfDayEnd;

						gettimeofday(&timeOfDayStart, NULL);

						wait(pid);
						
						rUsage = getrusage(RUSAGE_SELF,&usage);
						
						wallClockTime = gettimeofday(&timeOfDayEnd, NULL);
						
						afficherStats(pid, usage, wallClockTime, rUsage, timeOfDayStart, timeOfDayEnd);

					} else {
						cmd[positionAjoutTache]._task = task;
						cmd[positionAjoutTache+1]._pid = pid;

						positionAjoutTache = positionAjoutTache + 3;
						task = task + 1;

						printf("[%d] %d\n", cmd[positionAjoutTache - 3]._task, cmd[positionAjoutTache - 2]._pid);
						pause();
					}
				}
			}
		}
		
	} while(1);
}

/***************************************************************
 *				Traitement de l'entrée utilisateur
 ***************************************************************/
int traitementEntree() {
	int len;
	char tempoTab[60] = "";

	if(fgets(str, 60, stdin) !=  NULL)
	{
		strcat(tempoTab,str);
		len = strlen(str);

		if(len > 0 && str[len-1] == '\n') {
			str[len-1] = '\0';
		}

		arg[0] = strtok(str," \n");
		i = 0;
							
		while (arg[i] != NULL) {
			i = i + 1;
			arg[i] = strtok (NULL, " \n");	
		}	
		
		if (strcmp(arg[i - 1], "&") == 0) {
			strcpy(cmd[positionAjoutTache + 2]._cmd,tempoTab);
		}
		return 1;
	}
	else return 0;
}

/***************************************************************
 *				Terminal - Afficher Statistiques
 ***************************************************************/
void afficherStats(int pid, struct rusage usage, int wallClockTime, int rUsage, struct timeval timeOfDayStart, struct timeval timeOfDayEnd){

	float timeUsed;
	float timeCPU;

	//Calcul du temps d'execution de la commande
	if ( wallClockTime == 0) {
		timeUsed = (((float)timeOfDayEnd.tv_sec - (float)timeOfDayStart.tv_sec) * 1000) + 
				   (((float)timeOfDayEnd.tv_usec - (float)timeOfDayStart.tv_usec) / 1000);
	}

	//Calcul du temps d'execution du CPU
	if ( rUsage == 0) {
		timeCPU = ((float)usage.ru_stime.tv_sec * (long)1000) + 
				  ((float)usage.ru_stime.tv_usec / (long)1000);
	}
	
	printf("\n\n***************** STATISTIQUES ******************\n");
	printf("*\n");
	printf("* PID Parent : %d\n", getpid());
	printf("* PID Enfant : %d\n", pid);
	printf("*\n");
	printf("* Time exec. : %f ms\n", timeUsed);	
	printf("* Time CPU :   %f ms\n", timeCPU);
	printf("*\n");
	printf("* Involuntary interruption : %ld\n", usage.ru_nivcsw);
	printf("* Voluntary interruption :   %ld\n", usage.ru_nvcsw);
	printf("*\n");
	printf("* Page faults :   %ld\n", usage.ru_majflt);
	printf("* Page reclaims : %ld\n", usage.ru_minflt);
	printf("*\n");
	printf("*************************************************\n\n");
}