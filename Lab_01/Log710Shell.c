#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>

/***************************************************************
 *	Titre:			Log710PowerShell - 01
 *
 *	Description:	Deuxieme partie du laboratoire.
 *					Execution d'une commande pour accéder à
 *					un interpréteur de commande shell pour 
 *					finalement afficher des statistiques 
 *					relatives a l'execution.
 *			
 *		
 *	Etudiants:		Alexandre Laroche
 *					Tiahiti Caspar
 *
 *	Cours:			LOG710
 *	Institution:	ETS
 *	
 *	Date:			19 septembre 2018
 *
 ***************************************************************/

/***************************************************************
 *					MAIN - Demarrer l'execution
 ***************************************************************/
int main (int argc, char* argv[]) {

	char *str[60];
	char *arg[3];
	int len;
	bool exitCmd = 0;

	do {

		printf("Log710Shell%> ");

		if(fgets(str, 60, stdin) !=  NULL){

			len = strlen(str); 
			
			if(len > 0 && str[len-1] == '\n') {
				str[len-1] = '\0';
			}

			arg[0] = strtok(str," \n");
			int i = 0;
							
			while (arg[i] != NULL){
				i = i + 1;
				arg[i] = strtok (NULL, " \n");	
			}
		}

		if(strcmp(arg[0], "exit") == 0){
			exitCmd = 1;
			exit(0);				
		} 
		else if (strcmp(arg[0], "cd") == 0) {
			chdir(arg[1]);	
		}	
		else {

			//Initialise le Package ID
			pid_t pid = fork(); 
		
			//Arret de l'execution si aucunes commandes n'est entrées.
			if (argc < 1){ erreurCommande(arg); }

			//Arret de l'execution si on retrouve une erreur de fork.
			if (pid <= -1){ erreurFork(); }

			//Processus Fils
			else if (pid == 0){ processusEnfant(arg); }

			//Processus Parent
			else if (pid > 0){ processusParent(pid, argv, arg); }
		}

	} while (1);
}

/***************************************************************
 *					Erreur - Aucunes commandes
 ***************************************************************/
void erreurCommande(char* arg[]){

	printf("\n\n***************** ERREUR ******************\n");
	printf("*   Veuillez entrer une commande valide   *\n");
	printf("*******************************************\n");
	printf("*\n");

	//Affiche commande entrée
	entrerCommande(arg);

	abort();
	exit(0);
}

/***************************************************************
 *					Terminal - Afficher la commande
 ***************************************************************/
void entrerCommande(char* arg[]){

	printf("* Commande : ");

	//Affiche entièrement la commande entrée
	for(int i = 0; arg[i] != '\0'; i++){
        printf(" %s", arg[i]);
	}

	printf("\n");
}

/***************************************************************
 *						Erreur - Fork
 ***************************************************************/
void erreurFork(){

	printf("\n\n****************** ERREUR *****************\n");
	printf("*     Duplication processus impossible    *\n");
	printf("*           Voir fonction fork()          *\n");
	printf("*******************************************\n");
	abort();
	exit(0);
}

/***************************************************************
 *						Processus - Enfant
 ***************************************************************/
void processusEnfant(char* arg[]){

	printf("\n");

	//Affiche l'information du repertoire selon la commande entrée
	execvp(arg[0], arg);
	
	//Arrêt de l'execution si la commande est inconnu
	erreurCommande(arg);	
	abort();
	exit(0);
}

/***************************************************************
 *						Processus - parent
 ***************************************************************/
void processusParent(int pid, char* argv[], char* arg[]){

	int rUsage = 1;
	int wallClockTime = 1;
	struct rusage usage;
	struct timeval start;
	struct timeval timeOfDayStart, timeOfDayEnd;

	//Temporel: démarrer
	gettimeofday(&timeOfDayStart, NULL);	

	//Attend le Package ID avant de continuer
	wait(pid);
	
	rUsage = getrusage(RUSAGE_SELF,&usage);
	
	//Temporel: arrêt 
	wallClockTime = gettimeofday(&timeOfDayEnd, NULL);
	
	//Calcul et affichage des resultats obtenus de la commande entrée
	afficherStats(pid, argv, arg, usage, wallClockTime, rUsage, timeOfDayStart, timeOfDayEnd);
}

/***************************************************************
 *				Terminal - Afficher Statistiques
 ***************************************************************/
void afficherStats(int pid, char* argv[], char* arg[], struct rusage usage, int wallClockTime, int rUsage, struct timeval timeOfDayStart, struct timeval timeOfDayEnd){

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
	entrerCommande(argv);
	entrerCommande(arg);
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