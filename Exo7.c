#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Exo7.h"


void cree_Reste_graphe(Reste_graphe *RG,int nbcl){
	(*RG).nbcl=nbcl;
	(*RG).SLz=(Cellule_som**)malloc(nbcl*sizeof(Cellule_som*));
	(*RG).SB=(Cellule_som***)malloc(nbcl*sizeof(Cellule_som**));
	(*RG).Taille_SB=(int**)malloc(nbcl*sizeof(int*));
	(*RG).taille_max=(int*)malloc(nbcl*sizeof(int));
	(*RG).cl_max=(int*)malloc(nbcl*sizeof(int));
	int i,j;
	for(i=0;i<nbcl;i++){
		(*RG).SB[i]=(Cellule_som**)malloc(nbcl*sizeof(Cellule_som*));
		(*RG).SLz[i]=(Cellule_som*)malloc(sizeof(Cellule_som));
		(*RG).SLz[i]=NULL;
		(*RG).Taille_SB[i]=(int*)malloc(nbcl*sizeof(int));
		(*RG).taille_max[i]=0;
		for(j=0;j<nbcl;j++){
			(*RG).SB[i][j]=(Cellule_som*)malloc(sizeof(Cellule_som));
			(*RG).SB[i][j]=NULL;
			(*RG).Taille_SB[i][j]=0;
		}
	}
}

void init_SLz_reste_graphe(Reste_graphe *RG,Cellule_som**LZ){
	Cellule_som* t=*LZ;
	int i;
	for(i=0;i<(*RG).nbcl;i++)
		(*RG).SLz[i]=NULL;
	while(t){
		for(i=0;i<(*RG).nbcl;i++)
			ajoute_liste_sommet(t->sommet, &(*RG).SLz[i]);
		t=t->suiv;
	}
}

/* Teste si le sommet donn'e en parametre est deja dans la sous bordure de la version couleur cl de Reste_bordure, si oui la fonction renvoie vrai(1), faux(0) sinon */
int test_reste_bordure_cl_1(Sommet **s,int cl){
	if ((*s)->reste_bordure[cl]==1)return 1;
	return 0;
}

/* Affiche le statue reste_bordure de tous les sommets (celui-ci indique si le sommet est déjà dans la bordure de couleur i) */
void affiche_reste_bordure_sommet(Sommet **s, int nbcl){
	int i;
	printf("sommet->num : %d\n",(*s)->num);
	for (i=0;i<nbcl;i++){
		printf("reste_bordure[%d]: %d\n",i,(*s)->reste_bordure[i]);
	}
}

void affiche_marque_sommet(Cellule_som **som){
	Cellule_som *t=*som;
	while(t){
		printf("sommet %d : cl: %d / marque=%d\n",t->sommet->num,t->sommet->cl,t->sommet->marque);
		t=t->suiv;
	}
}

void affiche_version_cl(Cellule_som **B,int nbcl){
	Cellule_som *t=*B;
	while(t){
		printf("sommet %d : version=%d\n",t->sommet->num,t->sommet->version);
		t=t->suiv;
	}
}

void affiche_version_bordure(Cellule_som ***B,int nbcl){
	Cellule_som **TB=*B; 
	int i,j; 	
	for(i=0;i<nbcl;i++){
		affiche_version_cl(&TB[i],nbcl);
	}	
}

void maj_reste_SLz_i(Cellule_som **B, int cl,Reste_graphe *RG){
	Cellule_som *t=*B; 
	while(t){
		t->sommet->version=cl;
		ajoute_liste_sommet(t->sommet, &(*RG).SLz[cl]);
		t=t->suiv;
	}
}
		

void maj_reste_SLz(Cellule_som ***B, Bordure_graphe *BG,Reste_graphe *RG){
	int i,j;
	Cellule_som **TB=*B; 	
	for(i=0;i<(*RG).nbcl;i++){
		maj_reste_SLz_i(&TB[i], i,RG);
	}
	
}

void max_Taille_SB_cl(Reste_graphe *RG,Bordure_graphe *BG){
	int i,j,max;
	for(i=0;i<(*RG).nbcl;i++){
		max=0;
		for(j=0;j<(*RG).nbcl;j++){
			if((*RG).Taille_SB[i][j] > max){
				max=(*RG).Taille_SB[i][j];
				(*RG).taille_max[i]=max + (*BG).taille[i];
				(*RG).cl_max[i]=j;
				
			}
		}
	}
}


void maj_reste_adj(Cellule_som **adj, Reste_graphe *RG, int cl_inondation){
	Cellule_som *t=*adj;
	while(t){
		if(sommet_appartient_Zsg(&t->sommet)==0 && (t->sommet->version!=cl_inondation) && test_reste_bordure_cl_1(&t->sommet,cl_inondation)==0){
			t->sommet->reste_bordure[cl_inondation]=1;
			ajoute_liste_sommet(t->sommet, &((*RG).SB[cl_inondation][t->sommet->cl]));
			(*RG).Taille_SB[cl_inondation][t->sommet->cl]=(*RG).Taille_SB[cl_inondation][t->sommet->cl] + t->sommet->nbcase_som;
		}
		t=t->suiv;
	}
	

}

/* MAJ de du tableau des sous bordures, on donne en parametre une version possible du prochain ZSG (vlz) et la couleur de l'inondation de celle ci et on met a jour le bordure correspondante dans RG */
void maj_reste_par_cl(Cellule_som **vlz, Reste_graphe *RG, int cl_inondation){
	Cellule_som *t=*vlz;
	while(t){
		maj_reste_adj(&t->sommet->sommet_adj,RG,cl_inondation);
		t=t->suiv;
	}
}


/* Reprend les fonctions precedentes pour initialis'e le Reste_graphe avec Bordure_graphe, on a 'a la fin Reste_graphe totalement a jour */
void init_maj_Reste_graphe(Reste_graphe *RG, Bordure_graphe *BG){
	init_SLz_reste_graphe(RG,&(*BG).Lz);
	maj_reste_SLz(&(*BG).B,BG,RG);	
	int i;
	for(i=0;i<(*RG).nbcl;i++){	
		maj_reste_par_cl(&(*RG).SLz[i],RG, i);
	}max_Taille_SB_cl(RG,BG);
}

void affiche_Reste_graphe(Reste_graphe *RG){
	Reste_graphe R=*RG;
	printf("\nAffichage du Reste_graphe de %d couleurs:\n\n",(*RG).nbcl);
	printf(" + Sommet(s) des zones Zsg possibles au prochain changement de couleur: \n\n");
	int i,j;
	for(i=0;i<(*RG).nbcl;i++){
		printf("\tVersion inondation couleur_%d:\n\t\t",i);
		affiche_cellule_som(&((*RG).SLz[i]));
		printf("\n");
	}
	printf("\n\n");
	printf(" + Sommet(s) des prochaines Bordures par couleur:\n\n");
	
	for(i=0;i<(*RG).nbcl;i++){
		printf("\n\tVersion inondation couleur_%d:\n\n",i);
		for(j=0;j<(*RG).nbcl;j++){
			printf("\t\tCouleur %d -> ",j);
			affiche_cellule_som(&((*RG).SB[i][j]));
		}
	}
	printf("\n + Taille des prochaines Bordures par couleur:\n");
	for(i=0;i<(*RG).nbcl;i++){
		printf("___________________________________________________________\n");
		printf("\nTaille bordure de la version couleur_%d:\n",i);
		affiche_taille_bordure((*RG).Taille_SB[i],(*RG).nbcl);
		printf("\nCouleur la plus represent'ee de la version -> %d avec %d cases\n",(*RG).cl_max[i],(*RG).taille_max[i]);
	}
	printf("\n-----------------------------------------------------------\n");

}

void Remise_a_zero_Reste_graphe(Reste_graphe *RG,Cellule_som**som){
	int i,j;
	for(i=0;i<(*RG).nbcl;i++){
		detruit_liste_sommet(&((*RG).SLz[i]));
		(*RG).SLz[i]=NULL;
		(*RG).taille_max[i]=0;
		for(j=0;j<(*RG).nbcl;j++){
			detruit_liste_sommet(&((*RG).SB[i][j]));
			(*RG).SB[i][j]=NULL;
			(*RG).Taille_SB[i][j]=0;
		}
	}
	Cellule_som * t=*som;
	while(t){
		for(i=0;i<(*RG).nbcl;i++)
			t->sommet->reste_bordure[i]=0;
		t=t->suiv;
	}
}


/* Teste si un couleur n'a plus de sommet non visit'e dans le graphe. Si toutes les couleurs ont toujours au moins un sommet non visit'e, alors la fonction retourne -1.Si une couleur n'a pas de sommets non visit'e mais n'a que des sommets dans la zone Zsg alors res=-1 aussi. Si la couleur cl n'a aucun sommet non visit'e et a au moins un sommet de marque=1 alors on rend res=cl */
int test_aucun_sommet_visite_cl(Cellule_som** Lsom,int nbcl){
	Cellule_som * t;
	int cl,cpt1,cpt2;
	int res=-1;
	for(cl=0;cl<nbcl;cl++){
		t=*Lsom;
		res=cl;
		cpt1=0;cpt2=0;
		/* On teste si dans la liste sommet, il reste au moins un sommet de couleur cl non visit'e*/
		while(t){
			if(t->sommet->cl==cl && t->sommet->marque>1){
				res=-1;
				break;
			}
			t=t->suiv;
		}
		if(res==-1)continue;
		t=*Lsom;
		/* si on a toujours res=cl, on teste alors si au moins un de ces sommets est dans la bordure, si aucun alors on aura res=-1*/
		while(t){
			if(t->sommet->cl==cl && t->sommet->marque==1){
				cpt1++;
				break;
			}
			if(t->sommet->cl==cl && t->sommet->marque==0){
				cpt2++;
				//break;
			}
			t=t->suiv;	
		}
		if((cpt2!=0 && cpt1==0)||cpt1==0){
			res=-1;
			continue;
		}
		if(res==cl)break;
	}
	return res;
}
				
	
/* Teste dans le tableau des tailles de bordure de Reste_graphe, si au moins un des sous tableau de taille est vide, si oui elle rend vrai(1) sinon faux(0) */
int test_une_des_bordures_vide(int **tab, int nbcl){
	int i;
	for(i=0;i<nbcl;i++)
		if(test_bordure_vide(tab[i],nbcl)==1)return 1;
	return 0;
}



int max_Reste_Bordure(Grille *G, Reste_graphe *RG, Bordure_graphe *BG, Graphe_zone *GZ,int dim, int aff){
	int cpt,cl_max;
	cpt=0;
	if(sommet_appartient_Zsg(&((*GZ).mat[0][0]))==0)maj_Bordure_graphe(BG, (*GZ).mat[0][0]);
	

	while(test_bordure_vide((*BG).taille,(*BG).nbcl)!=1/* && cpt!=5*/){
		cpt++;
		/* Remplie Reste_Graphe en fonction de la bordure courante */
		init_maj_Reste_graphe(RG,BG);
		/* Choisit la meilleur couleur : le max de cases atteignable avec bordure + Reste */
		cl_max=test_aucun_sommet_visite_cl(&(*GZ).som,(*BG).nbcl);
		
		if(cl_max==-1){
			if(test_une_des_bordures_vide((*RG).Taille_SB,(*BG).nbcl)==0)
				cl_max=max_couleur((*RG).taille_max,(*BG).nbcl);
			else
				cl_max=max_couleur((*BG).taille,(*BG).nbcl);
		}
		
		/* Remet a zero Reste_Graphe pour pouvoir le re-remplir au prochain tour */
		Remise_a_zero_Reste_graphe(RG,&(*GZ).som);
		/* Maj de la bordure avec la couleur max */
		changement_cl_bordure(G,BG,GZ,cl_max,dim,aff);
	
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
	}
	return cpt;
}





