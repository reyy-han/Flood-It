#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include "Entete_Fonctions.h"
#include "S_Zsg.h"


void init_Zsg(int **M,int dim,int nbcl, S_Zsg **S){
	(*S)=(S_Zsg*)malloc(sizeof(S_Zsg));
	(*S)->dim=dim;
	(*S)->nbcl=nbcl;
	(*S)->Lzsg=NULL;
	(*S)->B=(ListeCase*)malloc(nbcl*sizeof(ListeCase));
	int i,j;
	for(i=0;i<nbcl;i++){
		(*S)->B[i]=(ListeCase)malloc(sizeof(ListeCase));
		(*S)->B[i]=NULL;
	}
	(*S)->App=(int**)malloc(dim*sizeof(int*));
	for(i=0;i<dim;i++){
		
		(*S)->App[i]=(int*)malloc(dim*sizeof(int));
		for(j=0;j<dim;j++){
			(*S)->App[i][j]=-2;	
		}
	}
}

int ajoute_Zsg(S_Zsg **S, int i, int j){
	(*S)->App[i][j]=-1;
	return ajoute_en_tete(&(*S)->Lzsg,i,j);
}

int ajoute_Bordure(S_Zsg **S, int i, int j,int cl){
	(*S)->App[i][j]=cl;
	return ajoute_en_tete(&(*S)->B[cl],i,j);
}

int appartient_Zsg(int i, int j, S_Zsg **S){
	if(((*S)->App[i][j])==-1)return 1;
	return 0;
}

int appartient_Bordure(int i, int j, S_Zsg **S){
	if(((*S)->App[i][j])>=0)return 1;
	return 0;
} 


int agrandit_Zsg(int**M, S_Zsg **Z, int cl,int k, int l){
	int cpt=0;
	ListeCase* P=(ListeCase*)malloc(sizeof(ListeCase));
	init_liste(P);

	/*on remplie notre pile avec les cases de la bordure de couleur cl*/
	ListeCase *B=(*Z)->B;
	while(B[cl]!=NULL){
		ajoute_en_tete(P,B[cl]->i,B[cl]->j);
		B[cl]=B[cl]->suiv;
	}
	ajoute_en_tete(P,k,l);
	
	/*On parcourt la liste des cases de Lzsg, qu'on met à jour à la couleur cl*/
	ListeCase L=malloc(sizeof(ListeCase));
	L=(*Z)->Lzsg;
	while(L!=NULL){
		M[L->i][L->j]=cl;
		L=L->suiv;
	}
	free(L);
	
	/*On traite toutes les cases de la pile: si la case courante (m,n) est de la bonne couleur alors on l'ajoute à Zsg et on ajoute ses voisins dans la pile P, sinon on l'ajoute à la bordure correspondante*/
	int m=-1;
	int n=-1;
	while(test_liste_vide(P)==0){
		enleve_en_tete(P,&m,&n);
		if(M[m][n]==cl){
			if(appartient_Zsg(m,n,Z)==0){
				ajoute_Zsg(Z,m,n);
				cpt++;
				if(m+1<((*Z)->dim))
					ajoute_en_tete(P,m+1,n);
				if(n+1<((*Z)->dim))
					ajoute_en_tete(P,m,n+1);
				if(m-1>=0)
					ajoute_en_tete(P,m-1,n);	
				if(n-1>=0)
					ajoute_en_tete(P,m,n-1);
			}
		}
		else{
			if(appartient_Bordure(m, n, Z)==0)
				ajoute_Bordure(Z, m, n, M[m][n]);		
		}
	}
	/*detruire les temporaires et la pile vide*/
	detruit_liste(P);
	return cpt;
}


int sequence_aleatoire_rapide(int**M, Grille *G, int dim, int nbcl, int aff){
	int nZsg=0;		/*nombre de cases dans la zone Zsg*/
	int chgt_cl=0;	/*nombre de changement de couleur effectue*/
	int rcl; 		/*futur random couleur*/
	S_Zsg *Z;
	init_Zsg(M,dim,nbcl,&Z);
	nZsg=nZsg+agrandit_Zsg(M,&Z,M[0][0],0,0);
	
	/*On change la couleur et on bascule les cases correspondantes jusqu'a inonder toute la grille*/
	while(nZsg!=(dim*dim)){
		rcl=(int)(rand()%nbcl);
		if(Z->B[rcl]!=NULL){
			nZsg=nZsg+agrandit_Zsg(M,&Z,rcl,Z->B[rcl]->i,Z->B[rcl]->j);
			chgt_cl++;
			if(aff==1){
				int i,j;
				Grille_init(dim,nbcl,500,&G);
				Grille_ouvre_fenetre(G);
				for (i=0;i<dim;i++){
    				for (j=0;j<dim;j++)
    					Grille_attribue_couleur_case(G,i,j,M[i][j]);
				}
				Grille_redessine_Grille();
				sleep(1);
			}
		}
	}
	return chgt_cl; 
}
