#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <time.h>
#include "Fonctions_exo5.h"


/*Fonction a utiliser si on choisit de ne pas initialiser la marque des sommets a 2 dans cree_graphe_zone*/
void init_marque_sommet(Cellule_som ** lsom,int marque){
	Cellule_som * t=*lsom;
	while(t){
		t->sommet->marque=marque;
		t=t->suiv;
	}
}

int sommet_appartient_Zsg(Sommet **s){
	if ((*s)->marque==0)return 1;
	return 0;
}

int sommet_appartient_Bordure(Sommet **s){
	if((*s)->marque==1)return 1;
	return 0;
} 

void init_Bordure_graphe(Bordure_graphe *BG,int nbcl){
	(*BG).nbcl=nbcl;
	(*BG).Lz=(Cellule_som*)malloc(sizeof(Cellule_som));
	(*BG).Lz=NULL;
	(*BG).B=(Cellule_som**)malloc(nbcl*sizeof(Cellule_som*));
	(*BG).taille=(int*)malloc(nbcl*sizeof(int));
	int i;
	for(i=0;i<nbcl;i++){
		(*BG).B[i]=(Cellule_som*)malloc(sizeof(Cellule_som));
		(*BG).B[i]=NULL;
		(*BG).taille[i]=0;
	}
}

void affiche_taille_bordure(int* tab,int nbcl){
	int i;
	for(i=0;i<nbcl;i++)
		printf("Taille de B[%d] : %d\n",i,tab[i]);
}

void colorie_cases_sommet(Grille *G, Cellule_som **Lsom, int cl){
	Cellule_som *t=*Lsom;
	while(t->sommet->cases){
		Grille_attribue_couleur_case(G,t->sommet->cases->i,t->sommet->cases->j,t->sommet->cl);
		t->sommet->cases=t->sommet->cases->suiv;
	}
}

void maj_couleur_sommet_mat(Cellule_som **Lsom, int cl){
	Cellule_som *t=*Lsom;
	while(t){
		t->sommet->cl=cl;
		t=t->suiv;
	}
}

void maj_bordure(Cellule_som **Ladj, Bordure_graphe *BG){
	Cellule_som *t=*Ladj;
	while(t){
		if(sommet_appartient_Zsg(&t->sommet)==0 && sommet_appartient_Bordure(&t->sommet)==0){
			t->sommet->marque=1;
			t->sommet->version=t->sommet->cl;
			ajoute_liste_sommet(t->sommet, &((*BG).B[t->sommet->cl]));
			(*BG).taille[t->sommet->cl]=(*BG).taille[t->sommet->cl] + t->sommet->nbcase_som;
		}
		t=t->suiv;
	}
}

void affiche_bordure(Bordure_graphe *BG){
	Bordure_graphe B=*BG;
	printf("\nAffichage de la Bordure_graphe de %d couleurs:\n\n",(*BG).nbcl);
	printf(" + Sommet(s) de la zone Zsg: \n\n");
	affiche_cellule_som(&((*BG).Lz));
	printf("\n");
	printf(" + Sommet(s) de la Bordure:\n\n");
	int i;
	for(i=0;i<(*BG).nbcl;i++){
		printf("\tCouleur %d -> ",i);
		affiche_cellule_som(&((*BG).B[i]));
	}
	printf("\n-----------------------------------------------------------\n");
}

/* Tres important pour initialiser la bordure. si on ne lance pas cette fonction sur l'origine le reste ne fonctionnera pas car ce ne sera pas initialis'e */
void maj_Bordure_graphe(Bordure_graphe *BG, Sommet * s){
	int nvCl=s->cl;
	Cellule_som * tz=(*BG).Lz;
	/* Colorie la zone Zsg avec la couleur du sommet s : */
	maj_couleur_sommet_mat(&(tz),nvCl);
	/* Ajout du sommet s dans la zone Zsg de la structure Bordure_graphe */
	s->marque=0;
	ajoute_liste_sommet(s, &(*BG).Lz);
	/* Maj des nouveaux sommets adjacents : marque=1 et ajout des sommets adjacents a la liste bordure */
	maj_bordure(&(s->sommet_adj), BG);
}


int test_bordure_vide(int *tab, int nbcl){
	int i;
	for(i=0;i<nbcl;i++)
		if(tab[i]!=0)return 0;
	return 1;
}

int max_couleur(int *tab, int nbcl){
	int i,max,res;
	max=0;
	res=0;
	for(i=0;i<nbcl;i++)
		if(tab[i]>max){
			max=tab[i];
			res=i;
		}
	return res;
}

int max_bordure(Grille *G, Bordure_graphe *BG, Graphe_zone *GZ,int dim, int aff){
	int cpt,cl_max;
	cpt=0;
	if(sommet_appartient_Zsg(&((*GZ).mat[0][0]))==0)maj_Bordure_graphe(BG, (*GZ).mat[0][0]);
	while(test_bordure_vide((*BG).taille,(*BG).nbcl)!=1){
		cpt++;
		cl_max=max_couleur((*BG).taille,(*BG).nbcl);
		(*BG).taille[cl_max]=0;
		Cellule_som * C=(*BG).B[cl_max];
		while(C){
			maj_Bordure_graphe(BG, C->sommet);
			C=C->suiv;
		}
	
		if(aff==1){
			int i,j;
			Grille_init(dim,(*BG).nbcl,500,&G);
			Grille_ouvre_fenetre(G);
			for (i=0;i<dim;i++){
   				for (j=0;j<dim;j++){
   					Grille_attribue_couleur_case(G,i,j,(*GZ).mat[i][j]->cl);
   				}
			}
			Grille_redessine_Grille();
			sleep(1);
		}
		detruit_liste_sommet(&((*BG).B[cl_max]));
		//affiche_bordure(BG);
	}
	return cpt;
}

/* Permet d'effectuer un seul changement de couleur sans passer par max_bordure*/
void changement_cl_bordure(Grille *G,Bordure_graphe *BG, Graphe_zone *GZ,int cl,int dim, int aff){
	
	(*BG).taille[cl]=0;
	Cellule_som * C=&(*(*BG).B[cl]);
	while(C){
		maj_Bordure_graphe(BG, C->sommet);
		C=C->suiv;
	}
	//maj_Bordure_graphe(BG, cl_max);

	if(aff==1){
		int i,j;
		Grille_init(dim,(*BG).nbcl,500,&G);
		Grille_ouvre_fenetre(G);
		for (i=0;i<dim;i++){
   			for (j=0;j<dim;j++){
   				Grille_attribue_couleur_case(G,i,j,(*GZ).mat[i][j]->cl);
   			}
		}
		Grille_redessine_Grille();
		sleep(1);
	}
	detruit_liste_sommet(&((*BG).B[cl]));
	//affiche_bordure(BG);
}
















