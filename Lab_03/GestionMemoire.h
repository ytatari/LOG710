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

#define SUCCES 0
#define ECHEC -1



/***************************************************************	 		
 *	Titre:	FIRST FIT			
 ***************************************************************/
int firstFit(noeud *memOrigine, int taille);

/***************************************************************	 		
 *	Titre:	BEST FIT				
 ***************************************************************/
int bestFit(noeud *memOrigine, int taille);

/***************************************************************	 		
 *	Titre:	WORST FIT				
 ***************************************************************/
int worstFit(noeud *memOrigine, int taille);

/***************************************************************	 		
 *	Titre:	NEXT FIT				
 ***************************************************************/
int nextFit(noeud *memOrigine, noeud *noeudOrigine, int taille);



/***************************************************************	 				
 ***************************************************************/


/***************************************************************	 		
 *	Description:		Structure qui garde en memoire
 						l'information du bloc.		
 ***************************************************************/
typedef struct memBloc {	
    int 	etatBloc;
    int 	tailleBloc;
    u_long 	adresseBloc;
} memBloc;

/***************************************************************	 		
 *	Description:		Structure qui permet de lier les blocs.	
 ***************************************************************/
typedef struct noeud {
    memBloc *valeur;
    struct 	noeud *precedent;
    struct 	noeud *suivant;
} noeud;

/***************************************************************	 		
 *	Description:	Initialise les structures de donnes 
 					du gestionnaire.				
 ***************************************************************/
noeud *initMem(int taille);

/***************************************************************	 		
 *	Description:	Alloue un nouveau bloc memoire			
 ***************************************************************/
noeud *allouMem(int taille, noeud *mem);

/***************************************************************	 		
 *	Description:	Libere un bloc memoire similaire a free()			
 ***************************************************************/
noeud *libereMem(noeud *pBloc);

/***************************************************************	 		
 *	Description:	Retourne le nombre de blocs de memoire libre		
 ***************************************************************/
int nBlocLibres(noeud *memOrigine);

/***************************************************************	 		
 *	Description:	Retourne le nombre de blocs alloues presentement		
 ***************************************************************/
int nBlocAlloues(noeud *memOrigine);

/***************************************************************	 		
 *	Description:	Retourne le nombre total de blocs mémoire libre 		
 ***************************************************************/
int memLibre(noeud *memOrigine);

/***************************************************************	 		
 *	Description:	Retourne la taille du plus grand bloc libre		
 ***************************************************************/
int mem_pGrand_libre(noeud *memOrigine);

/***************************************************************	 		
 *	Description:	Retourne le nombre de petit blocs non alloués		
 ***************************************************************/
int mem_small_free(noeud *memOrigine);

/***************************************************************	 		
 *	Description:	Retourne un octet en particulier alloué		
 ***************************************************************/
int mem_est_alloue(noeud *memOrigine);

/***************************************************************	 		
 *	Description:	Permet d'afficher l'état de la mémoire	
 ***************************************************************/
int afficher_mem(noeud *memOrigine);