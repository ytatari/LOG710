/***************************************************************
 *	Titre:			
 *
 *	Description:		Sénario de tests de
 *				méthodes d'allocations mémoire
 *		
 *	Etudiants:		Alexandre Laroche
 *				Tiahiti Caspar
 				Dominic Roberge
 *
 *	Cours:			LOG710
 *	Institution:		ETS
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
	noeud *mem = initMem(80);

	// Affiche l'état du bloc mémoire à l'origine
	afficher_etat(mem);
	// Affiche les fonctions de base des noeuds
	afficher_param(mem);

	// Test de FirstFit
	printf("\n - - - Test de FirstFit - - -\n\n0 = OK\n-1 = ERREUR\n\n");

	int ff1 = firstFit(mem, 10);
	printf(" - firstFit(10): %d\n", ff1);
	int ff2 = firstFit(mem, 5);
	printf(" - firstFit(5): %d\n", ff2);
	int ff3 = firstFit(mem, 1000);
	printf(" - firstFit(1000): %d\n", ff3);
	int ff4 = firstFit(mem, 5);
	printf(" - firstFit(5): %d\n", ff4);

	afficher_etat(mem);
	afficher_param(mem);

	// On efface le bloc de 5 à la position 2
	printf("\n - - - Libere le bloc #2 de 5 - - -\n\n");
	mem = premierNoeud(mem);
	mem = libereNoeudIndex(mem, 1);

	afficher_etat(mem);
	afficher_param(mem);

	// Test de BestFit
	printf("\n - - - Test de BestFit - - -\n\n0 = OK\n-1 = ERREUR\n\n");
	int bf1 = bestFit(mem, 10);
	printf(" - bestFit(10): %d\n", bf1);
	int bf2 = bestFit(mem, 5);
	printf(" - bestFit(5): %d\n", bf2);
	int bf3 = bestFit(mem, 1000);
	printf(" - bestFit(1000): %d\n", bf3);
	int bf4 = bestFit(mem, 25);
	printf(" - bestFit(25): %d\n", bf4);

	afficher_etat(mem);
	afficher_param(mem);

	// On efface le bloc de 5 à la position 2
	printf("\n - - - Libere le bloc #2 et #3 de 5 (deviens 1 bloc libre de 10) - - -\n\n");
	mem = premierNoeud(mem);
	mem = libereNoeudIndex(mem, 1);
	mem = premierNoeud(mem);
	mem = libereNoeudIndex(mem, 2);

	afficher_etat(mem);
	afficher_param(mem);

	// Test de WorstFit
	printf("\n - - - Test de WorstFit - - -\n\n0 = OK\n-1 = ERREUR\n\n");
	int wf1 = worstFit(mem, 10);
	printf(" - worstFit(10): %d\n", wf1);
	int wf2 = worstFit(mem, 5);
	printf(" - worstFit(5): %d\n", wf2);

	afficher_etat(mem);
	afficher_param(mem);

	// Test de NextFit
	printf("\n - - - Test de NextFit - - -\n\n0 = OK\n-1 = ERREUR\n\n");
	mem = premierNoeud(mem);
	mem = noeudIndex(mem, 3);
	printf(" - mem: Bloc #4\n");
	int nf1 = nextFit(mem, 5);
	printf(" - nextFit(5): %d\n", nf1);
	int nf2 = nextFit(mem, 5);
	printf(" - nextFit(5): %d\n", nf2);
	mem = premierNoeud(mem);
	printf(" - mem: Bloc #1\n");
	int nf3 = nextFit(mem, 5);
	printf(" - nextFit(5): %d\n", nf3);

	afficher_etat(mem);
	afficher_param(mem);

	// Test de mem_est_alloue
	printf("\n - - - Test de mem_est_alloue - - -\n\n1 = OUI\n0 = NON\n\n");
	mem = premierNoeud(mem);
	noeud *noeud1 = mem;
	int memAll1 = mem_est_alloue(mem, noeud1 -> valeur -> adresseBloc);
	printf(" - mem_est_alloue(%d): %d\n", noeud1 -> valeur -> adresseBloc, memAll1);
	noeud *noeud2 = noeudIndex(mem, 2);
	int memAll2 = mem_est_alloue(mem, noeud2 -> valeur -> adresseBloc);
	printf(" - mem_est_alloue(%d): %d\n", noeud2 -> valeur -> adresseBloc, memAll2);
	
	// Print de la fin
	printf("\n - - - Fin du sénario de tests - - -\n\n");

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
 *	Description:	Va chercher le premier bloc
 *			le plus petit possible
 *		
 ***************************************************************/
int bestFit(noeud *mem, int taille) {

	noeud *memOrigine = premierNoeud(mem);
	mem = memOrigine;

	int i = 0;
	int min = mem_pGrand_libre(mem);
	int minIndex = -1;
	int blocs = nBlocs(mem);

	while(mem != NULL) {
		// Vérifie que le bloc est non-alloué et suffisant ET...
		// que sa taille est inférieur au min 
		// OU que c'est le dernier bloc et sa taille est inférieur ou égale
		if((mem -> valeur -> etatBloc) == 0 && (mem -> valeur -> tailleBloc) >= taille &&
		  ((mem -> valeur -> tailleBloc) < min || (i == blocs-1 && (mem -> valeur -> tailleBloc) <= min))) {
			min = mem -> valeur -> tailleBloc;
			minIndex = i;
		}

		mem = mem -> suivant;
		i++;
	}

	// Si on a trouver un bloc qui convient
	if(minIndex >= 0) {
		mem = memOrigine;
		i = 0;

		while(mem != NULL) {
			if(i == minIndex) {
				// Alloue un nouveau bloc memoire
				allouMem(taille, mem);
				return SUCCES;
			}

			mem = mem -> suivant;
			i++;
		}
	}

	return ECHEC;
}

/***************************************************************
 *	Titre:			WORST FIT 		
 *
 *	Description:	Va chercher le premier bloc
 *			le plus grand
 *		
 ***************************************************************/
int worstFit(noeud *mem, int taille) {

	noeud *memOrigine = premierNoeud(mem);
	mem = memOrigine;

	int i = 0;
	int max = taille;
	int maxIndex = -1;

	while(mem != NULL) {
		// Vérifie que le bloc est non-alloué et suffisant ET...
		// que sa taille est supérieur ou égale au max
		if((mem -> valeur -> etatBloc) == 0 && (mem -> valeur -> tailleBloc) >= taille &&
		  (mem -> valeur -> tailleBloc) > max ) {
			max = mem -> valeur -> tailleBloc;
			maxIndex = i;
		}

		mem = mem -> suivant;
		i++;
	}

	// Si on a trouver un bloc qui convient
	if(maxIndex >= 0) {
		mem = memOrigine;
		i = 0;

		while(mem != NULL) {
			if(i == maxIndex) {
				// Alloue un nouveau bloc memoire
				allouMem(taille, mem);
				return SUCCES;
			}

			mem = mem -> suivant;
			i++;
		}
	}

	return ECHEC;
}

/***************************************************************
 *	Titre:			NEXT FIT 		
 *
 *	Description:	Variante de First Fit qui agis
 *			comme ce dernier mais ne commence pas
 *			au début mais à la référance donnée
 *		
 ***************************************************************/
int nextFit(noeud *mem, int taille) {
	// On commence directement la boucle avec le noeud donné
	// Si le noeud est le premier cela se comporte comme First Fit

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

