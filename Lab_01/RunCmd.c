#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

/***************************************************************
 *	Titre:			RunCmd
 *
 *	Description:	Premiere partie du laboratoire.
 *					Execution d'une commande pour afficher
 *					des statistiques relatives a l'execution.
 *			
 *		
 *	Etudiants:		Alexandre Laroche
 *					Tiahiti Caspar
 *
 *	Cours:			LOG710
 *	Institution:	ETS
 *	
 *	Date:			17 septembre 2018
 *
 ***************************************************************/


/***************************************************************
 *					MAIN - Demarrer l'execution
 ***************************************************************/
int main (int argc, char* argv[]) {

	//Initialise le Package ID
	pid_t pid = fork(); 

	//Arret de l'execution si aucunes commandes n'est entrées.
	if (argc <= 1){ erreurCommande(argv); }

	//Arret de l'execution si on retrouve une erreur de fork.
	if (pid <= -1){ erreurFork(); }

	//Processus Fils
	else if (pid == 0){ processusEnfant(argv); }

	//Processus Parent
	else if (pid > 0){ processusParent(pid, argv); }

	//Réussite de l'execution
	return 0;
}

/***************************************************************
 *					Erreur - Aucunes commandes
 ***************************************************************/
void erreurCommande(char* argv[]){

	printf("\n\n***************** ERREUR ******************\n");
	printf("*   Veuillez entrer une commande valide   *\n");
	printf("*******************************************\n");
	printf("*\n");

	//Affiche commande entrée
	entrerCommande(argv);

	abort();
	exit(0);
}

/***************************************************************
 *					Terminal - Afficher la commande
 ***************************************************************/
void entrerCommande(char* argv[]){

	printf("* Commande : ");

	//Affiche entièrement la commande entrée
	for(int i = 0; argv[i] != '\0'; i++){
        printf(" %s", argv[i]);
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
void processusEnfant(char* argv[]){

	printf("\n\n");

	//Affiche l'information du repertoire selon la commande entrée
	execvp(argv[1], &argv[1]);
	
	//Arrêt de l'execution si la commande est inconnu
	erreurCommande(argv);
	abort();
	exit(0);	
}

/***************************************************************
 *						Processus - parent
 ***************************************************************/
void processusParent(int pid, char* argv[]){

	int rUsage = 1;
	int wallClockTime = 1;
	struct rusage usage;
	struct timeval start;
	struct timeval timeOfDayStart, timeOfDayEnd;


	if (getrusage(RUSAGE_SELF, &usage) == 0) {
		start = usage.ru_stime;
	}

	//Temporel: démarrer
	gettimeofday(&timeOfDayStart, NULL);	
	gettimeofday(&start, NULL);

	//Attend le Package ID avant de continuer
	wait(pid);
	
	//Temporel: arrêt 
	wallClockTime = gettimeofday(&timeOfDayEnd, NULL);
	rUsage = getrusage(RUSAGE_SELF,&usage);

	//Calcul et affichage des resultats obtenus de la commande entrée
	afficherStats(pid, argv, usage, wallClockTime, rUsage, timeOfDayStart, timeOfDayEnd);
}

/***************************************************************
 *				Terminal - Afficher Statistiques
 ***************************************************************/
void afficherStats(int pid, char* argv[], struct rusage usage, int wallClockTime, int rUsage, struct timeval timeOfDayStart, struct timeval timeOfDayEnd){

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
