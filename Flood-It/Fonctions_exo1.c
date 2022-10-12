#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include "Entete_Fonctions.h"
#include "Liste_case.h"

void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){
	int color= M[i][j];
	ajoute_en_tete(L,i,j);
	M[i][j]=-1;
	(*taille)=(*taille)+1;
	if(i+1<nbcase)
		if(M[i+1][j]==color)
			trouve_zone_rec(M, nbcase, i+1, j, taille, L);
	if(j+1<nbcase)
		if(M[i][j+1]==color)
			trouve_zone_rec(M, nbcase, i, j+1, taille, L);
	if(i-1>=0)
		if(M[i-1][j]==color)
			trouve_zone_rec(M, nbcase, i-1, j, taille, L);
	if(j-1>=0)
		if(M[i][j-1]==color)
			trouve_zone_rec(M, nbcase, i, j-1, taille, L);
}


int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){
	int taille=0;
	int i,j,c,o,color,c1;
	color=M[0][0];
	c1=color;
	ListeCase *L=(ListeCase*) malloc(sizeof(ListeCase));
	init_liste(L);
	trouve_zone_rec(M,dim,0,0,&taille,L);
	srand(time(NULL));
	
	if((taille)==dim*dim){
		return 0;
	}
	else{
		while(color==c1){
			color=(int)(rand()%nbcl); // on choisit aleatoirement une couleur differente de celle à la case (0,0)
		}
		while(*L){
			// on colorie la zone deja inondee par la nouvelle couleur piochee precedement
			M[(*L)->i][(*L)->j]=color;
			(*L)=(*L)->suiv;
		}
		if(aff==1){
			Grille_init(dim,nbcl,500,&G);
			Grille_ouvre_fenetre(G);
			for (i=0;i<dim;i++){
    				for (j=0;j<dim;j++){
					Grille_attribue_couleur_case(G,i,j,M[i][j]);
	     			}
			}
			Grille_redessine_Grille();
		}
		sleep(1);
		(taille)=0;
		detruit_liste(L);
		return 1+sequence_aleatoire_rec(M,G,dim,nbcl,aff);
		}
	}
