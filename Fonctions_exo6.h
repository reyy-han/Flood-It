#ifndef __Fonctions_exo6__
#define __Fonctions_exo6__
#include "Liste_case.h"
#include "API_Grille.h"
#include "Fonctions_exo4.h"
#include "Fonctions_exo5.h"

typedef struct sequence Sequence;
struct sequence{
	int cl;	/* peut etre utilise pour le numero du sommet ou le numero de couleur */
	Sequence* suiv;
};

/* renvoie le numero du plus petit sommet adjacent */
int num_plus_petit_sommet_adj(Cellule_som** Sadj,int nbsom);

void affiche_sequence(Sequence ** S);

void detruit_sequence(Sequence ** S);

void ajoute_en_tete_sequence(Sequence **S,int cl);

/* Renvoie la liste chainee des changements de couleur à faire pour atteindre le zone inferieur droite */
void sequence_couleur_chemin_plus_court(Sequence **S,Graphe_zone *GZ,int i, int j, int k, int l);

/* Permet d'incorporer la zone inferieur droite dans la zone Zsg (rend le nombre de changement de couleur effectuer (utilise la sequence de couleur la plus courte possible : methode couleur)) */		
int atteint_inferieur_droite(Grille *G, Bordure_graphe *BG, Graphe_zone *GZ,Sequence **S, int dim, int aff);


/* 6.2 */
/* Permet d'attribuer les distances et pere correspondant aux chemins partant de u. Attention il faut que le parametre dist soit initialisé à 0 avant d'appeler la fonction */
void distance_pere(Sommet* u,Sommet *pere,int *dist);

/* Remplit la liste de sommet chemin_som avec les sommets du chemin le plus court entre les sommets u et v */
void parcours(Cellule_som ** chemin_som, Sommet* u, Sommet* v);

/* Affichage d'un chemin court entre u et v */
void affiche_parcours(Cellule_som ** chemin_som,Sommet* u, Sommet* v);

void affiche_dist(Cellule_som ** C);

/* Permet d'incorporer la zone inferieur droite dans la zone Zsg en utilisant la liste la plus courte possibles de sommet */
int Strategie_inferieur_droite(Grille *G, Bordure_graphe *BG, Graphe_zone *GZ, Cellule_som **C, int dim, int aff);























#endif
