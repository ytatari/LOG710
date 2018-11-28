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
 *	Titre:			MAIN 		
 *
 *	Description:	
 *			
 *		
 ***************************************************************/
int main(){

	//Initialise la memoire
	noeud *origine = initMem(1024);

	//Affiche l'état du bloc mémoire à l'origine
	afficher_mem(origine);

	//
	firstFit(origine, 128);

	//
	bestFit(origine, 128);

	//
	worstFit(origine, 128);

	//
	nextFit(origine, origine, 128);

	return SUCCES;
}

/***************************************************************
 *	Titre:			FIRST FIT 		
 *
 *	Description:	
 *			
 *		
 ***************************************************************/
int firstFit(noeud *memOrigine, int taille){

	noeud *mem = memOrigine;

	while(mem != NULL){

		//Vérifie si le bloc memoire est à son point initial
		if((mem -> valeur -> etatBloc) == 0 ){

			//
			if((mem -> valeur -> tailleBloc) >= taille){
				
				//Alloue un nouveau bloc memoire
				allouMem(taille, mem);
				return 0;
			}
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
int bestFit(noeud *memOrigine, int taille){
	return NULL;
}

/***************************************************************
 *	Titre:			WORST FIT 		
 *
 *	Description:	
 *			
 *		
 ***************************************************************/
int worstFit(noeud *memOrigine, int taille){
	return NULL;
}

/***************************************************************
 *	Titre:			NEXT FIT 		
 *
 *	Description:	
 *			
 *		
 ***************************************************************/
int nextFit(noeud *memOrigine, noeud *noeudOrigine, int taille){
	return NULL;
}

