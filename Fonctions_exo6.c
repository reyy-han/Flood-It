#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <time.h>
#include "Fonctions_exo6.h"

/* renvoie le numero du plus petit sommet adjacent */
int num_plus_petit_sommet_adj(Cellule_som** Sadj,int nbsom){
	Cellule_som* t=*Sadj;
	if(*Sadj==NULL){
		printf("Erreur : la liste de sommets_adjacents est NULL\n");
		return -1;
	}
	int	num_min=nbsom;
	while(t){
		if(t->sommet->num < num_min)
			num_min=t->sommet->num;
		t=t->suiv;
	}
	return num_min;
}

void affiche_sequence(Sequence ** S){
	Sequence* t=*S;
	if(t==NULL){
		printf("Aucune couleur\n");
		return;
	}printf("Affiche sequence couleur :  ");
	while(t){
		printf("%d ; ",t->cl);
		t=t->suiv;
	}
	printf("\n");
}	
	
void detruit_sequence(Sequence ** S){
	Sequence *cour,*temp;
  	cour=(*S);
  	while (cour!=NULL){
    temp=cour;
    cour=cour->suiv;
    free(temp);
  }
  *S=NULL;
}

void ajoute_en_tete_sequence(Sequence **S,int cl){
	Sequence *t;
	t=(Sequence*)malloc(sizeof(Sequence));
	if (t==NULL) 
    	return;
    
	t->suiv=*S;
	t->cl=cl;
	(*S)=t;	
    
}
/* Renvoie la liste chainee des changements de couleur à faire pour atteindre le zone inferieur droite */
void sequence_couleur_chemin_plus_court(Sequence **S,Graphe_zone *GZ,int i, int j, int k, int l){
	int minsom,tmp;
	Sommet * s_depart;
	Sommet *s_fin;
	Sommet * sc;
	if(i>k || j>l){
		printf("Erreur : il faut que les premieres coordonnees donnees (i,j) soient plus petites que les deuxiemes(k,l)\n");
		return;
	}
	s_depart=(*GZ).mat[i][j];
	//printf("s_depart->num: %d\n",s_depart->num);
	s_fin=(*GZ).mat[k][l];
	//printf("s_fin->num: %d\n",s_fin->num);
	sc=s_fin;
	Cellule_som * adj;
	while(sc->num!=s_depart->num){
		ajoute_en_tete_sequence(S,sc->cl);
		minsom=(*GZ).nbsom;
		adj=&(*sc->sommet_adj);
		while(adj){
			if(adj->sommet->num < sc->num){
				tmp=num_plus_petit_sommet_adj(&(adj->sommet->sommet_adj),(*GZ).nbsom);
				if(tmp < minsom || adj->sommet->num==s_depart->num){
					minsom=tmp;
					sc=adj->sommet;
				}
			}
			adj=adj->suiv;
		}
	}
}	

/* Permet d'incorporer la zone inferieur droite dans la zone Zsg (methode couleur) */		
int atteint_inferieur_droite(Grille *G, Bordure_graphe *BG, Graphe_zone *GZ, Sequence **S, int dim, int aff){
	int cpt=0;
	Sequence * t=*S;
	Cellule_som * BCl;
	if(sommet_appartient_Zsg(&((*GZ).mat[0][0]))==0)maj_Bordure_graphe(BG, (*GZ).mat[0][0]);
	while(t){
		cpt++;		
		BCl=(*BG).B[t->cl];
		(*BG).taille[t->cl]=0;
		while(BCl){
			maj_Bordure_graphe(BG, BCl->sommet);
			BCl=BCl->suiv;
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
		detruit_liste_sommet(&((*BG).B[t->cl]));
		t=t->suiv;
	} 
	detruit_sequence(S);
	return cpt;
}

void affiche_dist(Cellule_som ** C){
	Cellule_som * t=*C;
	if(t==NULL){
		printf("Aucun sommet\n");
		return;
	}
	printf("\nAffiche distance des sommets:\n");
	while(t){
		printf("%d(dist_%d) ;\n",t->sommet->num,t->sommet->distance);
		t=t->suiv;
	}
	printf("\n");
}	

/* Permet d'attribuer les distances et pere correspondant pour un chemin entre u et v. Attention il faut que le parametre dist soit initialisé à 0 avant d'appeler la fonction */
void distance_pere(Sommet* u,Sommet *pere,int *dist){
	if(u->distance <= (*dist))return;
	u->distance=*dist;
	u->pere=pere;
	int pro=(*dist)+1;
	Cellule_som * A=&(*u->sommet_adj);
	while(A){
		distance_pere(A->sommet,u,&pro);
		A=A->suiv;
	}
}

void parcours(Cellule_som ** chemin_som, Sommet* u, Sommet* v){
	*chemin_som=NULL;
	Sommet* cour;
	int dist=0;
	/* On attribut les distances et pere avec la fonction distance_pere */
	distance_pere(u,NULL,&dist);
	/* On remonte les peres pour les ajouter à la liste chainee de sommet chemin_som */
	cour=v;
	while(cour->distance!=0){
		ajoute_liste_sommet(cour,chemin_som);
		cour=cour->pere;
	}
	ajoute_liste_sommet(u,chemin_som);
}

void affiche_parcours(Cellule_som ** chemin_som,Sommet* u, Sommet* v){
	Cellule_som *t=*chemin_som;
	printf("Affichage du chemin le plus court entre les sommets %d et %d :\n",u->num,v->num);
	printf("%d(%d,",t->sommet->num,t->sommet->num);
	t=t->suiv;
	while(t){
		if(t->suiv==NULL)printf("%d)%d",t->sommet->num,t->sommet->num);
		else{printf("%d)%d(%d,",t->sommet->num,t->sommet->num,t->sommet->num);}
		t=t->suiv;
	}
	printf("\n\n");
}


int Strategie_inferieur_droite(Grille *G, Bordure_graphe *BG, Graphe_zone *GZ, Cellule_som **C, int dim, int aff){
	int cpt=0;
	maj_Bordure_graphe(BG, (*GZ).mat[0][0]);
	Cellule_som* t=*C;
	Cellule_som * BCl;
	while(t){
		if(sommet_appartient_Zsg(&t->sommet)==1){
			t=t->suiv;		
		}
		else{
			cpt++;		
			BCl=(*BG).B[t->sommet->cl];
			(*BG).taille[t->sommet->cl]=0;
			while(BCl){
				maj_Bordure_graphe(BG, BCl->sommet);
				BCl=BCl->suiv;
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
			detruit_liste_sommet(&((*BG).B[t->sommet->cl]));
			t=t->suiv;	
		}
	}
	detruit_liste_sommet(C);
	return cpt;
}






