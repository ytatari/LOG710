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

#define TRUE 1
#define FALSE 0


/***************************************************************	 		
 *	Description:		Structure qui garde en memoire
 *				l'information du bloc.		
 ***************************************************************/
typedef struct memBloc {	
    int 	etatBloc;
    int 	tailleBloc;
    u_long 	adresseBloc;
} memBloc;

/***************************************************************	 		
 *	Description:		Structure qui permet de lier 
 *				les blocs.	
 ***************************************************************/
typedef struct noeud {
    memBloc *valeur;
    struct 	noeud *precedent;
    struct 	noeud *suivant;
} noeud;



/***************************************************************	 				
 ***************************************************************/



/***************************************************************	 		
 *	Titre:	FIRST FIT			
 ***************************************************************/
int firstFit(noeud *mem, int taille);

/***************************************************************	 		
 *	Titre:	BEST FIT				
 ***************************************************************/
int bestFit(noeud *mem, int taille);

/***************************************************************	 		
 *	Titre:	WORST FIT				
 ***************************************************************/
int worstFit(noeud *mem, int taille);

/***************************************************************	 		
 *	Titre:	NEXT FIT				
 ***************************************************************/
int nextFit(noeud *mem, int taille);




/***************************************************************	 				
 ***************************************************************/



/***************************************************************	 		
 *	Description:	Initialise les structures de donnes 
 					du gestionnaire.				
 ***************************************************************/
noeud *initMem(int taille);

/***************************************************************	 		
 *	Description:	Initialise l'information du noeud			
 ***************************************************************/
noeud *initNoeud(memBloc *bloc);

/***************************************************************	 		
 *	Description:	Alloue un nouveau bloc memoire			
 ***************************************************************/
noeud *allouMem(int taille, noeud *mem);

/***************************************************************	 		
 *	Description:	Libere un bloc memoire similaire a free()			
 ***************************************************************/
noeud *libereMem(noeud *pBloc);

/***************************************************************	 		
 *	Description:	Donne le premier noeud de la chaine			
 ***************************************************************/
noeud *premierNoeud(noeud *mem);

/***************************************************************	 		
 *	Description:	Libere un bloc de la chaine à un index			
 ***************************************************************/
noeud *libereNoeudIndex(noeud *memOrigine, int index);

/***************************************************************	 		
 *	Description:	Retourne le noeud ou NULL à un index		
 ***************************************************************/
noeud *noeudIndex(noeud *memOrigine, int index);

/***************************************************************	 		
 *	Description:	Retourne le nombre de blocs de memoire	
 ***************************************************************/
int nBlocs(noeud *memOrigine);

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
int mem_small_free(noeud *memOrigine, int maxTaillePetit);

/***************************************************************	 		
 *	Description:	Retourne un octet en particulier alloué		
 ***************************************************************/
int mem_est_alloue(noeud *memOrigine, int pOctet);

/***************************************************************	 		
 *	Description:	Permet d'afficher l'état de la mémoire	
 ***************************************************************/
void afficher_etat(noeud *mem);

/***************************************************************	 		
 *	Description:	Permet d'afficher les parametres memoire
 ***************************************************************/
void afficher_param(noeud *mem);
