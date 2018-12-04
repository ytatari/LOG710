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
#include "StructureData.h"

/***************************************************************
 *	Titre:			INITIALISER MEMOIRE 		
 *
 *	Description:	Initialise les structures de donnes 
 *					du gestionnaire.					
 *					
 ***************************************************************/
noeud *initMem(int taille){

	//Creation d'un bloc d'espace memoire
	memBloc *bloc = malloc(sizeof(memBloc));

	//Initialise les parametres du bloc
	bloc -> etatBloc 	= 0;
	bloc -> tailleBloc	= taille;
	bloc -> adresseBloc = malloc(taille);
	
	//Démarre l'initialisation du noeud
	return initNoeud(bloc);
}

/***************************************************************
 *	Titre:			INITIALISER NOEUD		
 *
 *	Description:	Initialise l'information du noeud
 *			
 ***************************************************************/
noeud *initNoeud(memBloc *bloc){

	//Allocation de l'espace memoire du noeud
	noeud *origine = malloc(sizeof(noeud));

	//Initialise les parametres du noeud
	origine -> valeur    = bloc;
	origine -> precedent = NULL;
	origine -> suivant   = NULL;

	return origine;
}

/***************************************************************
 *	Titre:			ALLOUER MEMOIRE 		
 *
 *	Description:	Alloue un nouveau bloc memoire sur le noeud
 *				
 ***************************************************************/
noeud *allouMem(int taille, noeud *mem){

	// Condition de vérification
	if((mem -> valeur -> etatBloc) == 0 && (mem -> valeur -> tailleBloc) >= taille) {

		// Creation d'un nouveau bloc d'espace memoire
		memBloc *bloc = malloc(sizeof(memBloc));

		// Initialise les parametres du nouveau bloc
		bloc -> etatBloc 	= 1;
		bloc -> tailleBloc 	= taille;
		bloc -> adresseBloc 	= mem -> valeur -> adresseBloc;
		
		// Si le bloc non-alloué est vidé on le remplace
		if((mem -> valeur -> tailleBloc) == taille) {
			//memBloc *blocLibre = mem -> valeur;
			//mem -> valeur = NULL;
			//free(blocLibre);
			
			mem -> valeur = bloc;
		
		// Sinon on crée un nouveau noeud au début du libre
		} else {
			// Allocation d'un nouvel space memoire du noeud
			noeud *noeud = malloc(sizeof(noeud));
			noeud -> valeur = bloc;

			// Changement des valeurs du bloc non-alloué
			mem -> valeur -> adresseBloc += taille;
			mem -> valeur -> tailleBloc  -= taille;

			// Le précédent du nouveau noeud est l'ancien du libre
			noeud -> precedent = mem -> precedent;

			// Si le noeud non-alloué a un précédent
			// ce dernier a pour suivant le nouveau noeud
			if(noeud -> precedent != NULL)
				noeud -> precedent -> suivant = noeud;

			// Le précédent du noeud est le nouveau
			mem -> precedent = noeud;

			// Le suivant du nouveau noeud est celui libre
			noeud -> suivant = mem;
		}
	}

	return mem;
}

/***************************************************************
 *	Titre:			LIBERER MEMOIRE 		
 *
 *	Description:	Libere un bloc memoire similaire a free()
 *		
 ***************************************************************/
noeud *libereMem(noeud *mem) {
	// L'état du bloc est maintenant libre
	mem -> valeur -> etatBloc = 0;

	noeud *blocPrecedent = mem -> precedent;
	noeud *blocSuivant   = mem -> suivant;

	// Condition pour traiter le bloc (noeud) precedent.
	if(blocPrecedent -> valeur -> etatBloc == 0){

		// On change la position du bloc et sa taille en additionnant
		mem -> valeur -> adresseBloc = blocPrecedent -> valeur -> adresseBloc;
		mem -> valeur -> tailleBloc += blocPrecedent -> valeur -> tailleBloc;

		// Le bloc précedent le bloc libre est assigné au bloc
		mem -> precedent = blocPrecedent -> precedent;

		// Si le bloc précedent le bloc libre existe,
		// son suivant devient celui libéré
		if(blocPrecedent -> precedent != NULL)
			blocPrecedent -> precedent -> suivant = mem;

		// Libere l'espace memoire du bloc precedent
		free(blocPrecedent);
	}
	// Condition pour traiter le bloc (noeud) suivant.
	else if(blocSuivant -> valeur -> etatBloc == 0) {

		// On additione l'espace libre du suivant
		mem -> valeur -> tailleBloc += blocSuivant -> valeur -> tailleBloc;
		
		// Le bloc suivant du bloc libre est assigné au bloc
		mem -> suivant = blocSuivant -> suivant;
		
		// Si le bloc suivant du bloc libre existe,
		// son précedent devient celui libéré
		if(blocSuivant -> suivant != NULL)
			blocSuivant -> suivant -> precedent = mem;

		// Libere l'espace memoire du bloc suivant
		free(blocSuivant);
	}
	return mem;
}

/***************************************************************
 *	Titre:			PREMIER NOEUD DE LA CHAINE		
 *
 *	Description:	Retourne le premier noeud de la chaine
 *				
 ***************************************************************/
noeud *premierNoeud(noeud *mem) {
	while(mem -> precedent != NULL) {
		mem = mem -> precedent;
	}
	return mem;
}

/***************************************************************
 *	Titre:		Libère le noeud à partir de l'index	
 *
 *	Description:	Retourne le noeud libéré si possible
 *				
 ***************************************************************/
noeud *libereNoeudIndex(noeud *memOrigine, int index) {
	int i = 0;

	noeud *mem = memOrigine;

	while(mem != NULL) {
		if(i == index) {
			return libereMem(mem);
		}

		mem = mem -> suivant;
		i++;
	}

	return mem;
}

/***************************************************************
 *	Titre:			NOMBRE BLOCS 		
 *
 *	Description:	Retourne le nombre de blocs
 *				
 ***************************************************************/
int nBlocs(noeud *memOrigine) {

	int nBlocs = 0;
	noeud *mem = memOrigine;

	while(mem != NULL){
		nBlocs += 1;
		mem = mem -> suivant;
	}
	return nBlocs;
}

/***************************************************************
 *	Titre:			NOMBRE BLOCS LIBRES 		
 *
 *	Description:	Retourne le nombre de blocs de memoire libre
 *				
 ***************************************************************/
int nBlocLibres(noeud *memOrigine){

	int nBlocs = 0;
	noeud *mem = memOrigine;

	while(mem != NULL){
		
		//
		if(mem -> valeur -> etatBloc == 0) 
			nBlocs += 1;
		mem = mem -> suivant;
	}
	return nBlocs;
}

/***************************************************************
 *	Titre:			NOMBRE BLOCS ALLOUÉS 		
 *
 *	Description:	Retourne le nombre de blocs alloues presentement
 *				
 ***************************************************************/
int nBlocAlloues(noeud *memOrigine){

	int nBlocAll = 0;
	noeud *mem = memOrigine;

	while(mem != NULL){

		//
		if(mem -> valeur -> etatBloc == 1)
			nBlocAll += 1;
		mem = mem -> suivant;
	}
	return nBlocAll;
}

/***************************************************************
 *	Titre:			NOMBRE BLOCS TOTAL LIBRE 		
 *
 *	Description:	Retourne le nombre total de blocs mémoire 
 *					libre (non alloué) 
 *				
 ***************************************************************/
int memLibre(noeud *memOrigine){

	int mLib = 0;
	noeud *mem = memOrigine;

	while(mem != NULL){

		//
		if(mem -> valeur -> etatBloc == 0)
			mLib += mem -> valeur -> tailleBloc;
		mem = mem -> suivant;
	}
	return mLib;
}

/***************************************************************
 *	Titre:			TAILLE PLUS GRAND BLOC 		
 *
 *	Description:	Retourne la taille du plus grand bloc libre
 *			
 ***************************************************************/
int mem_pGrand_libre(noeud *memOrigine) {

    int tGraBloc = 0;
    noeud *mem = memOrigine;

    while (mem != NULL) {

    	///Vérifie si le bloc memoire est à son point initial
        if((mem -> valeur -> etatBloc) == 0){

        	//
			if((mem -> valeur -> tailleBloc) > tGraBloc)
       			tGraBloc = mem -> valeur -> tailleBloc;
       	}
        mem = mem -> suivant;
    }
    return tGraBloc;
}

/***************************************************************
 *	Titre:			NOMBRE PETITS BLOCS LIBRE 		
 *
 *	Description:	Retourne le nombre de petit blocs non alloués
 *					(plus petit que taille maxTaillePetit)
 *					
 ***************************************************************/
int mem_small_free(noeud *memOrigine) {

	int maxTaillePetit = 0;

	// À continuer
}

/***************************************************************
 *	Titre:			MEMOIRE EN PARTICULIER ALLOUÉ 		
 *
 *	Description:	Retourne un octet en particulier alloué		
 *			
 *		
 ***************************************************************/
int mem_est_alloue(noeud *memOrigine) {

	int pOctet = 0;

	// À continuer
}

/***************************************************************
 *	Titre:			AFFICHER ETAT MÉMOIRE		
 *
 *	Description:	Permet d'afficher l'état de la mémoire
 *			
 *		
 ***************************************************************/
void afficher_etat(noeud *mem) {
	mem = premierNoeud(mem);

	printf("\n\n********************************\n");
	printf("Voici l'état des blocs mémoire:\n\n");

	int i = 1;

	while (mem != NULL) {
		printf("Bloc #%d:\n", i);
		printf("État:\t\t%d\n", mem -> valeur -> etatBloc);
		printf("Taille:\t\t%d\n", mem -> valeur -> tailleBloc);
		printf("Adresse:\t%d\n\n", mem -> valeur -> adresseBloc);
		mem = mem -> suivant;
		i++;
	}
}

/***************************************************************
 *	Titre:			AFFICHER PARAMETRE MÉMOIRE		
 *
 *	Description:	Permet d'afficher les parametres memoire
 *			
 *		
 ***************************************************************/
void afficher_param(noeud *mem) {
	mem = premierNoeud(mem);

	printf("\n\n********************************\n");
	printf("Voici les paramètres mémoire:\n\n");
	printf("Blocs libres :\t%d\n", nBlocLibres(mem));
	printf("Blocs alloués :\t%d\n", nBlocAlloues(mem));
	printf("Mémoire libre :\t%d\n", memLibre(mem));
	printf("Taille max :\t%d\n\n", mem_pGrand_libre(mem));

}

