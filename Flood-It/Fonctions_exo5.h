#ifndef __Fonctions_exo5__
#define __Fonctions_exo5__
#include "Liste_case.h"
#include "API_Grille.h"
#include "Fonctions_exo4.h"


typedef struct bordure_graphe{
	int nbcl; 	/* Nombre de couleurs */
	Cellule_som * Lz;	/* Liste des pointeurs sur sommet de la zone Zsg */
	Cellule_som **B; 	/* Tableau de nbcl listes chain'ees de pointeurs sur sommets-zones de la bordure */
	int *taille;		/* Tableau des tailles de chaque liste correspondant aux couleurs dans la bordure */

} Bordure_graphe;



void init_marque_sommet(Cellule_som ** lsom,int marque);

int sommet_appartient_Zsg(Sommet **s);

int sommet_appartient_Bordure(Sommet **s);

void init_Bordure_graphe(Bordure_graphe *BG,int nbcl);

void affiche_taille_bordure(int* tab,int nbcl);

void colorie_cases_sommet(Grille *G, Cellule_som **Lcase, int cl);

void maj_couleur_sommet_mat(Cellule_som **Lsom, int cl);

/* Met a jour la bordure de BG en rajoutant les sommets de la liste Ladj (sommets adjacents) si pas dans la zone et pas encore dans la bordure */
void maj_bordure(Cellule_som **Ladj, Bordure_graphe *BG);

void affiche_bordure(Bordure_graphe *BG);

/* Ajoute le sommet s dans la zone Zsg et met a jour la liste des sommets Lz et la bordure de Bordure_graphe B et il recolorie la Zone zsg */
void maj_Bordure_graphe(Bordure_graphe *BG, Sommet * s);

/* Teste si la bordure est vide pour toute les couleurs du graphe */
int test_bordure_vide(int *tab, int nbcl);

/* Rend le numero du sommet qui a plusieurs sommets dans la bordure */
int max_couleur(int *tab, int nbcl);

/* Strategie max_bordure : fini lorsque la bordure est vide pour toutes les couleurs et rend le nombre d'essais */
int max_bordure(Grille *G, Bordure_graphe *BG, Graphe_zone *GZ, int dim, int aff);

void changement_cl_bordure(Grille *G,Bordure_graphe *BG, Graphe_zone *GZ,int cl,int dim, int aff);
#endif
