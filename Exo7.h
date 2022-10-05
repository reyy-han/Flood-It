#ifndef __Exo7__
#define __Exo7__
#include "Liste_case.h"
#include "API_Grille.h"
#include "Fonctions_exo4.h"
#include "Fonctions_exo5.h"
#include "Fonctions_exo6.h"



typedef struct reste_graphe{
	int nbcl; 	/* Nombre de couleurs */
	Cellule_som ** SLz;	/* Tableau de nbcl Listes des pointeurs sur sommet de la zone Zsg potentielle (si la couleur bascule au prochain changement de couleur) */
	Cellule_som ***SB; 	/* Tableau de Tableau de nbcl listes chain'ees de pointeurs sur sommets-zones des possibles prochaines bordures */
	int ** Taille_SB;	/* Tableau de Tableau des tailles des sous_bordure */
	int *taille_max;	/* Tableau des tailles_max possible avec chaque version de ZSG possible */
	int *cl_max;		/* Tableau des num de couleur dans taille_max par versions */
	//int *taille_pre;	/* Tableau des tailles de la bordure precedentes pas encore inondé */
} Reste_graphe;

void cree_Reste_graphe(Reste_graphe *RG,int nbcl);

void init_SLz_reste_graphe(Reste_graphe *RG,Cellule_som**LZ);

int test_reste_bordure_cl_1(Sommet **s,int cl);

/* Affiche le statue reste_bordure de tous les sommets (celui-ci indique si le sommet est déjà dans la bordure de couleur i) */
void affiche_reste_bordure_sommet(Sommet **s, int nbcl);

void affiche_marque_sommet(Cellule_som **som);

void affiche_version_cl(Cellule_som **B,int nbcl);

void affiche_version_bordure(Cellule_som ***SB,int nbcl);

void maj_reste_SLz_i(Cellule_som **B, int cl,Reste_graphe *RG);

void maj_reste_SLz(Cellule_som ***B, Bordure_graphe *BG, Reste_graphe *RG);

void max_Taille_SB_cl(Reste_graphe *RG,Bordure_graphe *BG);

void maj_reste_adj(Cellule_som **adj, Reste_graphe *RG, int cl_inondation);

/* MAJ de du tableau des sous bordures, on donne en parametre une version possible du prochain ZSG (vlz) et la couleur de l'inondation de celle ci et on maj jour le bordure correspondante dans RG */
void maj_reste_par_cl(Cellule_som **vlz, Reste_graphe *RG, int cl_inondation);

/* Reprend les fonctions precedentes pour initialis'e le Reste_graphe avec Bordure_graphe, on a 'a la fin Reste_graphe totalement a jour */
void init_maj_Reste_graphe(Reste_graphe *RG, Bordure_graphe *BG);

void affiche_tab(int* tab,int nbcl);

void affiche_Reste_graphe(Reste_graphe *RG);

void Remise_a_zero_Reste_graphe(Reste_graphe *RG,Cellule_som**som);

/* Teste si un couleur n'a plus de sommet non visit'e dans le graphe. Si toutes les couleurs ont toujours au moins un sommet non visit'e, alors la fonction retourne -1.Si une couleur n'a pas de sommets non visit'e mais n'a que des sommets dans la zone Zsg alors res=-1 aussi. Si la couleur cl n'a aucun sommet non visit'e et a au moins un sommet de marque=1 alors on rend res=cl */
int test_aucun_sommet_visite_cl(Cellule_som** Lsom,int nbcl);
	
/* Teste dans le tableau des tailles de bordure de Reste_graphe, si au moins un des sous tableau de taille est vide, si oui elle rend vrai(1) sinon faux(0) */
int test_une_des_bordures_vide(int **tab, int nbcl);

int max_Reste_Bordure(Grille *G, Reste_graphe *RG, Bordure_graphe *BG, Graphe_zone *GZ,int dim, int aff);







#endif
