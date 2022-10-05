#include "Fonctions_exo4.h"
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Entete_Fonctions.h"


Sommet * cree_sommet(int num,int cl,int nbcl){
	Sommet * s=(Sommet *)malloc(sizeof(Sommet));
	s->num=num;
	s->cl=cl;
	s->cases=(Elnt_liste*) malloc(sizeof(Elnt_liste));
	if(s->cases==NULL)return NULL;
	init_liste(&s->cases);
	s->nbcase_som=0;
	s->marque=2;
	s->sommet_adj=(Cellule_som*)malloc(sizeof(Cellule_som));
	if(s->sommet_adj==NULL)return NULL;
	s->sommet_adj=NULL;
	s->distance=1000;
	s->pere=NULL;
	s->reste_bordure=(int *)malloc(nbcl*sizeof(int));
	if(s->reste_bordure==NULL)return NULL;
	int i;
	for(i=0;i<nbcl;i++)s->reste_bordure[i]=0;
	s->version=-1;
}
	


void ajoute_liste_sommet(Sommet * s, Cellule_som ** Lsom){
	Cellule_som *t= (Cellule_som*)malloc(sizeof(Cellule_som));
	if(t==NULL) {
		printf("erreur allocation\n");
		return;
	}
	t->sommet=s;
	t->suiv=(*Lsom);
	(*Lsom)=t;
}


void detruit_liste_sommet(Cellule_som **L){
	Cellule_som *t;
	while(*L!=NULL) {
		t=*L;
		(*L)=(*L)->suiv;
		free(t);
	}
}
	
void ajoute_voisin(Sommet * s1, Sommet *s2){
	ajoute_liste_sommet(s1,&(s2->sommet_adj));
	ajoute_liste_sommet(s2,&(s1->sommet_adj));

}

int adjacent(Sommet *s1, Sommet *s2){
	Sommet t=*s1;
	while(t.sommet_adj!=NULL){
		if(t.sommet_adj->sommet==s2){
			return 1;
		}t.sommet_adj=t.sommet_adj->suiv;
	}
	return 0;
} 
void detruit_liste_et_sommet(Cellule_som **L){
	Cellule_som *t;
	while(*L!=NULL) {
		t=*L;
		(*L)=(*L)->suiv;
		free(t->sommet);
		free(t);
	}
}

void trouve_zone_rec_exo4(Graphe_zone *G,Sommet *s,int **M, int nbcase, int i, int j, int *taille, ListeCase *L){
	int color= M[i][j];
	ajoute_en_tete(L,i,j);
	(*G).mat[i][j]=s;	
	(*taille)=(*taille)+1;
	if(i+1<nbcase){
		if(M[i+1][j]==color && (*G).mat[i+1][j]==NULL){
			trouve_zone_rec_exo4(G,s,M, nbcase, i+1, j, taille, L);
		}
	}if(j+1<nbcase)
		if(M[i][j+1]==color && (*G).mat[i][j+1]==NULL)
			trouve_zone_rec_exo4(G,s,M, nbcase, i, j+1, taille, L);
	if(i-1>=0)
		if(M[i-1][j]==color && (*G).mat[i-1][j]==NULL)
			trouve_zone_rec_exo4(G,s,M, nbcase, i-1, j, taille, L);
	if(j-1>=0)
		if(M[i][j-1]==color && (*G).mat[i][j-1]==NULL)
			trouve_zone_rec_exo4(G,s,M, nbcase, i, j-1, taille, L);	
}
	
	
void cree_graphe_zone(Graphe_zone * G,int **M,int dim,int nbcl){
	int i,j,cpt=0;
	/* Initialisation a 0 du graphe */
	(*G).nbsom=0;
	(*G).som=(Cellule_som*)malloc(sizeof(Cellule_som));
	(*G).som=NULL;
	(*G).mat=(Sommet***)malloc(sizeof(Sommet**)*dim);
	for(i=0;i<dim;i++){
		(*G).mat[i]=(Sommet**)malloc(sizeof(Sommet*)*dim);
		for(j=0;j<dim;j++){
			(*G).mat[i][j]=(Sommet*)malloc(sizeof(Sommet));
			(*G).mat[i][j]=NULL;
		}
	}
	/* Pour chaque case (i,j), on initialise la matrice à NULL puis on détermine la zone correspondante */
	int taille;
	Sommet *s=(Sommet *) malloc(sizeof(Sommet));
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			taille=0;
			if((*G).mat[i][j]==NULL){
				/* Création du sommet pour l'origine (i,j) */
				(s)=cree_sommet(cpt,M[i][j],nbcl);
				cpt++;
				//(*G).mat[i][j]=(Sommet*)malloc(sizeof(Sommet));
				init_liste(&((s)->cases)); /* Liste vide de cases */
				trouve_zone_rec_exo4(G,s,M,dim,i,j,&taille,&((s)->cases));
				(s)->nbcase_som=taille;
				ajoute_liste_sommet(s,&((*G).som));
				(*G).nbsom++;
			}
		}
   		
	
	}
	/* On indique les sommets voisins*/
	for(i=0;i<dim;i++)
		for(j=0;j<dim;j++){	
			if(i+1<dim)
				if((*G).mat[i][j]!=(*G).mat[i+1][j] && adjacent((*G).mat[i][j],(*G).mat[i+1][j])==0)
					ajoute_voisin((*G).mat[i][j],(*G).mat[i+1][j]);
			if(j+1<dim)
				if((*G).mat[i][j]!=(*G).mat[i][j+1] && adjacent((*G).mat[i][j],(*G).mat[i][j+1])==0)
					ajoute_voisin((*G).mat[i][j],(*G).mat[i][j+1]);
			if(i-1>=0)
				if((*G).mat[i][j]!=(*G).mat[i-1][j] && adjacent((*G).mat[i][j],(*G).mat[i-1][j])==0)
					ajoute_voisin((*G).mat[i][j],(*G).mat[i-1][j]);
			if(j-1>=0)
				if((*G).mat[i][j]!=(*G).mat[i][j-1] && adjacent((*G).mat[i][j],(*G).mat[i][j-1])==0)
					ajoute_voisin((*G).mat[i][j],(*G).mat[i][j-1]);
		}
	
}

void affiche_liste_cases(ListeCase * L){
	ListeCase t=*L; 
	if(t==NULL){
		printf("Aucune case\n");
		return;
	}
	while(t){
		printf("(%d,%d) ; ",t->i,t->j);
		t=t->suiv;
	}
	printf("\n");
}

void affiche_cellule_som(Cellule_som ** C){
	Cellule_som * t=*C;
	if(t==NULL){
		printf("Aucun sommet\n");
		return;
	}
	while(t){
		printf("%d ; ",t->sommet->num);
		t=t->suiv;
	}
	printf("\n");
}	
	
void affiche_Graphe_zone(Graphe_zone * G,int **M){
	Graphe_zone Z= *G;
	printf("\nAffichage du Graphe_zone de %d sommet(s) :\n",Z.nbsom);
	while(Z.som){
		printf("Sommet: %d (cl_%d)\n\tCases: ",Z.som->sommet->num,Z.som->sommet->cl);
		affiche_liste_cases(&(Z.som->sommet->cases));
		
		printf("\tSommets adjacents: ");
		affiche_cellule_som(&(Z.som->sommet->sommet_adj));
		
		Z.som=Z.som->suiv;
		printf("-----------------------------------------------------------\n");
	}
		
}
