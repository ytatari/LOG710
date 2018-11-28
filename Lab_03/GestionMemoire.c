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
#include "GestionMemoire.h"

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
	initNoeud(bloc);
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
 *	Description:	Alloue un nouveau bloc memoire	
 *				
 ***************************************************************/
noeud *allouMem(int taille, noeud *mem){

	//Condition de verification ?

	//Creation d'un nouveau bloc d'espace memoire
    memBloc *bloc = malloc(sizeof(memBloc));

    //Initialise les parametres du nouveau bloc
    bloc -> etatBloc 	= 1
    bloc -> tailleBloc 	= taille;
    bloc -> adresseBloc = mem -> valeur -> adresseBloc;

    mem -> valeur -> adresseBloc += taille;
    mem -> valeur -> tailleBloc  -= taille;

	//Allocation d'un nouvel space memoire du noeud
  	noeud *noeud = malloc(sizeof(noeud));
  	noeud *pBloc = noeud;
  	
  	//Initialise les parametres du nouveau noeud
  	noeud -> valeur 	= bloc;
  	noeud -> precedent  = mem -> precedent;
  	noeud -> suivant    = mem;

  	mem -> precedent = noeud;

  	return pBloc;
}

/***************************************************************
 *	Titre:			LIBERER MEMOIRE 		
 *
 *	Description:	Libere un bloc memoire similaire a free()
 *		
 ***************************************************************/
noeud *libereMem(noeud *pBloc){

	pBloc -> valeur -> etat = 0;

	noeud *blocPrecedent = pBloc -> precedent;
	noeud *blocSuivant   = pBloc -> suivant;

	//Condition pour traiter le bloc (noeud) precedent.
	if(blocPrecedent -> valeur -> etat == 0){

		//
		pBloc -> valeur -> adresseBloc = blocPrecedent -> valeur -> adresseBloc;
		pBloc -> valeur -> tailleBloc += blocPrecedent -> valeur -> tailleBloc;

		//
		pBloc -> precedent = blocPrecedent -> precedent;
		pBloc -> precedent -> precedent = pBloc;

		//Libere l'espace memoire du bloc precedent
		free(blocPrecedent);
	}
	//Condition pour traiter le bloc (noeud) suivant.
	else if(blocSuivant -> valeur -> etat == 0){

		//
		pBloc -> valeur -> tailleBloc += blocSuivant -> valeur -> tailleBloc
		
		//
		pBloc -> suivant = blocSuivant -> suivant;
		pBloc -> suivant -> precedent = pBloc

		//Libere l'espace memoire du bloc suivant
		free(blocSuivant);
	}
	return pBloc;
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
		if(mem -> valeur -> etat == 0) 
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
		if(mem -> valeur -> etat == 1)
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
		if(mem -> valeur -> etat == 0)
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

    	//
        if ((mem -> valeur -> etat == 0) && (mem -> valeur -> tailleBloc > tGraBloc))
       		tGraBloc = mem -> valeur -> tailleBloc;
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
 *	Titre:			AFFICHER MÉMOIRE		
 *
 *	Description:	Permet d'afficher l'état de la mémoire
 *			
 *		
 ***************************************************************/
void afficher_mem(noeud *memOrigine) {

	printf("\n\n********************************\n");
	printf("Voici l'état des blocs mémoire:\n\n");

	// À continuer
}