#ifndef __S_Zsg__
#define __S_Zsg__
#include "Liste_case.h"

typedef struct s_Zsg{
	int dim; 	/*dimension de la grille*/
	int nbcl; 	/*nombre de couleurs*/

	ListeCase Lzsg; /*Liste des cases de la zone Zsg*/
	ListeCase *B; 	/*Tableau de listes de cases de la bordure*/
	int **App; 	/*Tableau a double entree des appartenances*/
} S_Zsg;


void init_Zsg(int **M,int dim,int nbcl,S_Zsg **S);
int ajoute_Zsg(S_Zsg **Z, int i, int j);
int ajoute_Bordure(S_Zsg **Z, int i, int j,int cl);
int appartient_Zsg(int i, int j, S_Zsg **S);
int appartient_Bordure(int i, int j, S_Zsg **S);

int agrandit_Zsg(int**M, S_Zsg **Z, int cl,int k, int l);
int sequence_aleatoire_rapide(int**M, Grille *G, int dim, int nbcl, int aff);

#endif

