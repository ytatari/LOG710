/***************************************************************
 *	Titre:			
 *
 *	Description:	
 *			
 *		
 *	Etudiants:		Alexandre Laroche
 *					Tiahiti Caspar
 					Dominic Kanrabat
 *
 *	Cours:			LOG710
 *	Institution:	ETS
 *	
 *	Date:			21 novembre 2018
 *
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "GestionMemoire.c"

/***************************************************************
 *	Titre:			MAIN 		
 *
 *	Description:	
 *			
 *		
 ***************************************************************/
int main() {

	// Initialise la memoire
	noeud *origine = initMem(80);

	// Affiche l'état du bloc mémoire à l'origine
	afficher_etat(origine);

	// Affiche les fonctions de base des noeuds
	afficher_param(origine);

	// Test de FirstFit
	printf("\n- - - Test de FirstFit - - -\n\n0 = OK\n-1 = ERREUR\n\n");

	int ff1 = firstFit(origine, 10);
	printf("firstFit(10): %d\n", ff1);
	int ff2 = firstFit(origine, 5);
	printf("firstFit(5): %d\n", ff2);
	int ff3 = firstFit(origine, 1000);
	printf("firstFit(1000): %d\n", ff3);
	int ff4 = firstFit(origine, 5);
	printf("firstFit(5): %d\n", ff4);

	origine = premierNoeud(origine);
	afficher_etat(origine);
	afficher_param(origine);

	// On efface le bloc de 5 à la position 2
	printf("\n- - - Libere le bloc #2 de 5 - - -\n\n");
	origine = libereNoeudIndex(origine, 1);
	origine = premierNoeud(origine);
	afficher_etat(origine);
	afficher_param(origine);

	// Test de BestFit
	printf("\n- - - Test de BestFit - - -\n\n0 = OK\n-1 = ERREUR\n\n");
	int bf1 = bestFit(origine, 5);
	printf("bestFit(5): %d\n", bf1);

	// Test de WorstFit
	worstFit(origine, 128);

	// Test de NextFit
	nextFit(origine, origine, 128);

	return SUCCES;
}

/***************************************************************
 *	Titre:			FIRST FIT 		
 *
 *	Description:	Prend le premier bloc non-alloué
 *			disponible et le fractionne
 *		
 ***************************************************************/
int firstFit(noeud *mem, int taille){

	mem = premierNoeud(mem);

	while(mem != NULL) {
		// Vérifie si le bloc memoire est à son point initial
		// et que la taille est suffisante
		if((mem -> valeur -> etatBloc) == 0 && (mem -> valeur -> tailleBloc) >= taille) {
			// Alloue un nouveau bloc memoire
			allouMem(taille, mem);
			return SUCCES;
		}

		mem = mem -> suivant;
	}

	return ECHEC;
}

/***************************************************************
 *	Titre:			BEST FIT 		
 *
 *	Description:	
 *			
 *		
 ***************************************************************/
int bestFit(noeud *mem, int taille) {


	return ECHEC;
}

/***************************************************************
 *	Titre:			WORST FIT 		
 *
 *	Description:	
 *			
 *		
 ***************************************************************/
int worstFit(noeud *mem, int taille){
	return SUCCES;
}

/***************************************************************
 *	Titre:			NEXT FIT 		
 *
 *	Description:	
 *			
 *		
 ***************************************************************/
int nextFit(noeud *memOrigine, noeud *noeudOrigine, int taille){
	return SUCCES;
}

