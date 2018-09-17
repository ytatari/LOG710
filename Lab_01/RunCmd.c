#include <stdio.h>
#include <stdlib.h>

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
	
	//Arret de l'execution si aucunes commandes n'est entrées
	if (argc <= 1){ erreurCommande(); }

	//Packet Identifier
	int pid = fork();

	switch(pid) {

		//Erreur fork
		case -1:
			erreurFork();
		break;

		//Processus Fils
		case 0:
			processusFils(argv);
		break;

		//Processus Parent
		default:
			processusParent(pid, argc);
		break;
	}	

	//Réussite de l'execution de la commande
	return 0;
}

/***************************************************************
 *					Erreur - Aucune commande
 ***************************************************************/
void erreurCommande(){

	printf("\n*************** ERREUR ***************\n");
	printf("*   Vous devez entrer une commande   *\n");
	printf("**************************************\n\n");
	abort();
	exit(0);

}

/***************************************************************
 *						Erreur - Fork
 ***************************************************************/
void erreurFork(){

	printf("\n*************** ERREUR ***************\n");
	printf("*  Duplication processus impossible  *\n");
	printf("*        Voir fonction fork()        *\n");
	printf("**************************************\n\n");
	abort();
	exit(0);
}

/***************************************************************
 *						Processus - Fils
 ***************************************************************/
void processusFils(char* argv[]){

	//A faire...
	printf("FILS, id = %d\n");
	printf("l'argument est %d\n", argv[3]);
}

/***************************************************************
 *						Processus - parent
 ***************************************************************/
void processusParent(int pid, int argc){

	//A faire...
	printf("PARENT, pid = %d\n");
	printf("le id de mon fils = %d\n", pid);
	printf("toto %d\n", argc);
}



/*
	if (pid < 0){

		printf("fork(): %c\n", argv[1]);
		return 1;
	}
	else if (pid) {

		printf("PARENT, pid = %d\n");
		printf("le id de mon fils = %d\n", pid);
		printf("toto %d\n", argc);
	}
	else {

		printf("FILS, id = %d\n");
		printf("l'argument est %d\n", argv[3]);
		return 1;
	}
*/