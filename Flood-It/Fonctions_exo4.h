#ifndef __Fonctions_exo4__
#define __Fonctions_exo4__
#include "Liste_case.h"

typedef struct sommet Sommet;

/*Element d'une liste cha\^in\'ee de pointeurs sur sommets*/
typedef struct cellule_som{
	Sommet * sommet;
	struct cellule_som * suiv;
}Cellule_som;


struct sommet{
	int num;	/* Numero du Sommet (sert uniquement  a l'affichage) */
	int cl;		/* Couleur d'origine du sommet-zone */
	ListeCase cases;/* Listes des cases du sommet-zone */
	int nbcase_som;	/* Nombre de cases de cette liste */
	int marque;	/* statut du sommet (0=Zsg ; 1=bordure ; 2= non visit'e ; (exo 7: 3=reste) ) sera utilisé dans l'exercice 5 */
	
	Cellule_som * sommet_adj;	/* Liste des ar\^etes pointeurs sur les sommets adjacents */
	int distance;	/* Nombre d'aretes reliant ce sommet a la racine du parcours en largeur */
	Sommet * pere;	/* Pere du sommet dans l'arborescence du parcours en largeur */

	int * reste_bordure; /* Si la case bordure_reste[i]=1 alors le sommet est deja dans la bordure de la version de couleur i dans Reste_bordure (exo 7), bordure_reste[i]=0 sinon */
	int version;	/* egale au numero couleur du prochain zsg possible (exo 7), -1 a l'initialisation */
};


typedef struct graphe_zone{
	int nbsom;	/* Nombre de sommets dans le graphe */
	Cellule_som*som;/* Liste chainee des sommets du graphe */
	Sommet ***mat;	/* Matrice de pointeurs sur les sommets indiquant a quel sommet appartient une case (i,j) de la grille */
}Graphe_zone;


/* Cree et rend un pointeur sur sommet de parametre num et cl, initialise la liste de cases à vide et alloue la liste de sommets adjacents */
Sommet * cree_sommet(int num,int cl,int nbcl);

void ajoute_liste_sommet(Sommet * s, Cellule_som ** Lsom);

void detruit_liste_sommet(Cellule_som **Lsom);

void ajoute_voisin(Sommet * s1, Sommet *s2);

int adjacent(Sommet *s1, Sommet *s2); 

void detruit_liste_et_sommet(Cellule_som **L);

/* Version pour l'exo4 de trouver_zone_rec qui met à jour (*G).mat[i][j] au sommet donn'e en parametre */ 
void trouve_zone_rec_exo4(Graphe_zone *G,Sommet *s,int **M, int nbcase, int i, int j, int *taille, ListeCase *L);

void remplit_sommet_cases(Graphe_zone *G,Sommet *s,int **M, int nbcase, int i, int j, int *taille, ListeCase *L);

void cree_graphe_zone(Graphe_zone * G, int **M,int dim,int nbcl);

/* Fonction d'affichage */
void affiche_cellule_som(Cellule_som ** C);

void affiche_liste_cases(ListeCase * L);

void affiche_Graphe_zone(Graphe_zone * G,int **M);

#endif
