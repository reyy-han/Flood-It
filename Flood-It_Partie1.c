#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Entete_Fonctions.h"
#include "Liste_case.h"
#include "S_Zsg.h"
#include "Fonctions_exo4.h"
#include "Fonctions_exo5.h"
#include "Fonctions_exo6.h"
#include "Exo7.h"

int main(int argc,char**argv){
  srand(time(NULL));
  int dim, nbcl, nivdif, graine, exo, aff;
  Grille *G;
  int i,j;
  int **M;

  clock_t
    temps_initial, /* Temps initial en micro-secondes */
    temps_final;   /* Temps final en micro-secondes */
  float
    temps_cpu;     /* Temps total en secondes */ 
 


  if(argc!=7){
    printf("usage: %s <dimension> <nb_de_couleurs> <niveau_difficulte> <graine> <exo:0-1-3-4-5-6-7-13> <aff 0/1>\n",argv[0]);
    return 1;
  }

  dim=atoi(argv[1]);


  nbcl=atoi(argv[2]);
  nivdif=atoi(argv[3]);
  graine=atoi(argv[4]);
  exo=atoi(argv[5]);
  aff=atoi(argv[6]);

  /* Generation de l'instance */

  M=(int **) malloc(sizeof(int*)*dim);
  for (i=0;i<dim;i++){
    M[i]=(int*) malloc(sizeof(int)*dim);
    if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
  }

  Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);

  /* Affichage de la grille */
 
	
  if (aff==1){
    Grille_init(dim,nbcl, 500,&G);
    Grille_ouvre_fenetre(G);

    for (i=0;i<dim;i++)
      for (j=0;j<dim;j++){
	Grille_attribue_couleur_case(G,i,j,M[i][j]);
      }

    Grille_redessine_Grille();
    sleep(1);
  }

  temps_initial = clock ();
  
  if (exo==0){
     printf("%d essais\n", sequence_aleatoire_rec(M, G, dim, nbcl, aff)); 
  }
  if (exo==1){
	int taille=0;
	printf("%d essais\n", sequence_aleatoire_rec(M, G, dim, nbcl, aff)); 
  }
  if (exo==3){
	printf("%d essais\n", sequence_aleatoire_rapide(M, G, dim, nbcl, aff));

  }
  /*exo4*/
  if(exo==4){
	printf("Exercice 4:\n");
	
	/*Sommet *so=(Sommet*)malloc(sizeof(Sommet));
	so->num=1;
	so->cl=2;
	init_liste(&(so->cases));
	so->nbcase_som=1;
	so->sommet_adj=(Cellule_som*)malloc(sizeof(Cellule_som));
	Cellule_som * LC=(Cellule_som*)malloc(sizeof(Cellule_som));
	Sommet *st=cree_sommet(2,1);
	ajoute_liste_sommet(so,&LC);
	ajoute_liste_sommet(st,&LC);
	ajoute_voisin(so,st);
	
	if(adjacent(so,st)==0)printf("ne sont pas adjacents\n");
	if(adjacent(so,st)==1)printf("sont adjacents\n");
	printf("Destruction\n");
	detruit_liste_sommet(&LC);
	printf("num sommet supp: %d\n",so->num);
	printf("num sommet supp: %d\n",st->num);*/
	
	
	Graphe_zone *GZ=(Graphe_zone*)malloc(sizeof(Graphe_zone));
	cree_graphe_zone(GZ,M,dim,nbcl);
	affiche_Graphe_zone(GZ,M);

	/* Destruction du Graphe-zone */
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			/*if((*GZ).mat[i][j])*///free((*GZ).mat[i][j]);
		}if((*GZ).mat[i])free((*GZ).mat[i]);
	}if((*GZ).mat)free((*GZ).mat);
	detruit_liste_et_sommet(&((*GZ).som));
	free(GZ);
	
  }
  
  if(exo==5){
  
	printf("Exercice 5:\n");
	Graphe_zone *GZ=(Graphe_zone*)malloc(sizeof(Graphe_zone));
	cree_graphe_zone(GZ,M,dim,nbcl);
	
	//affiche_Graphe_zone(GZ,M);
	
	Bordure_graphe *BG=(Bordure_graphe*)malloc(sizeof(Bordure_graphe));
	init_Bordure_graphe(BG,nbcl);

	
	printf("%d essais\n",max_bordure(G, BG, GZ, dim, aff));
	
	//affiche_bordure(BG);
	//affiche_taille_bordure((*BG).taille,nbcl); /* Pas obligatoire */


	/* Destruction de la Bordure_graphe */
	detruit_liste_sommet(&((*BG).Lz));
	free((*BG).taille);
	for(i=0;i<nbcl;i++){
		if((*BG).B[i])detruit_liste_sommet(&((*BG).B[i]));
	}if((*BG).B)free((*BG).B);
	free(BG);
	
	/* Destruction du Graphe-zone */
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			/*if((*GZ).mat[i][j])*///free((*GZ).mat[i][j]);
		}if((*GZ).mat[i])free((*GZ).mat[i]);
	}if((*GZ).mat)free((*GZ).mat);
	detruit_liste_et_sommet(&((*GZ).som));
	free(GZ);
  }	

  if(exo==6){
	printf("Exercice 6:\n");

	Graphe_zone *GZ=(Graphe_zone*)malloc(sizeof(Graphe_zone));
	cree_graphe_zone(GZ,M,dim,nbcl);
	//affiche_Graphe_zone(GZ,M); /* Pas obligatoire */
	
	/* Initialisation : bordure completement vide */
	Bordure_graphe *BG=(Bordure_graphe*)malloc(sizeof(Bordure_graphe));
	init_Bordure_graphe(BG,nbcl);
	
	
	/* Creation de la liste de sommets du chemin le plus court entre l'origine et le sommet interieur droit, puis affichage de ce chemin */
	Cellule_som * C=(Cellule_som*)malloc(sizeof(Cellule_som));
	C=NULL;
	Sommet * sd, *sf;
	sd=(*GZ).mat[0][0];
	sf=(*GZ).mat[dim-1][dim-1];
	parcours(&C,sd,sf);
	//affiche_dist(&(*GZ).som); /* Pas obligatoire */
	affiche_parcours(&C,sd,sf);
	//affiche_cellule_som(&C);


	/* Creation de la liste des changements de couleurs a faire pour incorporer la zone inferieur droite de la grille (methode couleur implementer pour la question 6.1)*/
	/*Sequence *S=(Sequence*)malloc(sizeof(Sequence));
	S=NULL;
	sequence_couleur_chemin_plus_court(&S,GZ,0,0,dim-1,dim-1);
	affiche_sequence(&S); *//* Pas obligatoire */

	/* Incorporation de la zone inferieur droite (methode couleur) */
	//printf("%d essais\n",atteint_inferieur_droite(G,BG,GZ,&S,dim,aff)+ max_bordure(G,BG,GZ,dim,nbcl,aff));

	
	/* Incorporation de la zone inferieur droite (methode distance_sommet) */
	printf("%d essais\n",Strategie_inferieur_droite(G,BG,GZ,&C,dim,aff) + max_bordure(G,BG,GZ,dim,aff));
	

	//affiche_bordure(BG);
	/* Destruction de la Bordure_graphe */
	detruit_liste_sommet(&((*BG).Lz));
	free((*BG).taille);
	for(i=0;i<nbcl;i++){
		if((*BG).B[i])detruit_liste_sommet(&((*BG).B[i]));
	}if((*BG).B)free((*BG).B);
	free(BG);
	
	/* Destruction du Graphe-zone */
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			/*if((*GZ).mat[i][j])*///free((*GZ).mat[i][j]);
		}if((*GZ).mat[i])free((*GZ).mat[i]);
	}if((*GZ).mat)free((*GZ).mat);
	detruit_liste_et_sommet(&((*GZ).som));
	free(GZ);
	
  }
  if(exo==7){
	printf("Exercice 7:\n");

	Graphe_zone *GZ=(Graphe_zone*)malloc(sizeof(Graphe_zone));
	cree_graphe_zone(GZ,M,dim,nbcl);
	//affiche_Graphe_zone(GZ,M); /* Pas obligatoire */
	
	/* Initialisation : bordure completement vide */
	Bordure_graphe *BG=(Bordure_graphe*)malloc(sizeof(Bordure_graphe));
	init_Bordure_graphe(BG,nbcl);

	//maj_Bordure_graphe(BG, (*GZ).mat[0][0]);
	
	//affiche_version_bordure(&(*BG).B, nbcl);

	Reste_graphe *RG=(Reste_graphe*)malloc(sizeof(Reste_graphe));
	cree_Reste_graphe(RG,nbcl);
	
	/*init_maj_Reste_graphe(RG,BG);
	affiche_Reste_graphe(RG);
	affiche_bordure(BG);
	printf("\n________________________Remise_a_zero_____________________\n");
	Remise_a_zero_Reste_graphe(RG,&(*GZ).som);
	affiche_Reste_graphe(RG);
	printf("\n___________________Maj_bordure_cl_case_12___________________\n");
	changement_cl_bordure(G,BG,GZ,  (*GZ).mat[1][0]->cl,dim,aff);
	affiche_bordure(BG);
	printf("\n________________________init_maj_rste_____________________\n");
	init_maj_Reste_graphe(RG,BG);
	affiche_Reste_graphe(RG);*/
	/*affiche_bordure(BG);*/
	
	

	printf("%d essais\n",max_Reste_Bordure(G, RG, BG, GZ, dim, aff));
	
	/* Destruction de la Reste_graphe */
	free((*RG).taille_max);
	free((*RG).cl_max);
	for(i=0;i<nbcl;i++){
		free((*RG).Taille_SB[i]);
		if((*RG).SLz[i])detruit_liste_sommet(&((*RG).SLz[i]));
		for(j=0;j<nbcl;j++){
			if((*RG).SB[i][j])detruit_liste_sommet(&((*RG).SB[i][j]));
		}if((*RG).SB[i])detruit_liste_sommet(&(*(*RG).SB[i]));
	}if((*RG).SB)free(((*RG).SB));
	if((*RG).SLz)free((*RG).SLz);
	free((*RG).Taille_SB);
	free(RG);
	/* Destruction de la Bordure_graphe */
	detruit_liste_sommet(&((*BG).Lz));
	free((*BG).taille);
	for(i=0;i<nbcl;i++){
		if((*BG).B[i])detruit_liste_sommet(&((*BG).B[i]));
	}if((*BG).B)free((*BG).B);
	free(BG);
	
	/* Destruction du Graphe-zone */
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			/*if((*GZ).mat[i][j])*///free((*GZ).mat[i][j]);
		}if((*GZ).mat[i])free((*GZ).mat[i]);
	}if((*GZ).mat)free((*GZ).mat);
	detruit_liste_et_sommet(&((*GZ).som));
	free(GZ);
	
  } 
  if(exo==13){
	printf("Exercice 6 + 7:\n");
	Graphe_zone *GZ=(Graphe_zone*)malloc(sizeof(Graphe_zone));
	cree_graphe_zone(GZ,M,dim,nbcl);

	Bordure_graphe *BG=(Bordure_graphe*)malloc(sizeof(Bordure_graphe));
	init_Bordure_graphe(BG,nbcl);

	Reste_graphe *RG=(Reste_graphe*)malloc(sizeof(Reste_graphe));
	cree_Reste_graphe(RG,nbcl);
	
	Cellule_som * C=(Cellule_som*)malloc(sizeof(Cellule_som));
	C=NULL;
	Sommet * sd, *sf;
	sd=(*GZ).mat[0][0];
	sf=(*GZ).mat[dim-1][dim-1];
	parcours(&C,sd,sf);
	printf("%d essais\n",Strategie_inferieur_droite(G,BG,GZ,&C,dim,aff) + max_Reste_Bordure(G, RG, BG, GZ, dim, aff));


	/* Destruction de la Reste_graphe */
	free((*RG).taille_max);
	free((*RG).cl_max);
	for(i=0;i<nbcl;i++){
		free((*RG).Taille_SB[i]);
		if((*RG).SLz[i])detruit_liste_sommet(&((*RG).SLz[i]));
		for(j=0;j<nbcl;j++){
			if((*RG).SB[i][j])detruit_liste_sommet(&((*RG).SB[i][j]));
		}if((*RG).SB[i])detruit_liste_sommet(&(*(*RG).SB[i]));
	}if((*RG).SB)free(((*RG).SB));
	if((*RG).SLz)free((*RG).SLz);
	free((*RG).Taille_SB);
	free(RG);
	/* Destruction de la Bordure_graphe */
	detruit_liste_sommet(&((*BG).Lz));
	free((*BG).taille);
	for(i=0;i<nbcl;i++){
		if((*BG).B[i])detruit_liste_sommet(&((*BG).B[i]));
	}if((*BG).B)free((*BG).B);
	free(BG);
	
	/* Destruction du Graphe-zone */
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			/*if((*GZ).mat[i][j])*///free((*GZ).mat[i][j]);
		}if((*GZ).mat[i])free((*GZ).mat[i]);
	}if((*GZ).mat)free((*GZ).mat);
	detruit_liste_et_sommet(&((*GZ).som));
	free(GZ);
}

  temps_final = clock ();
  temps_cpu = (temps_final - temps_initial) * 1e-6;
  printf("temps_cpu : %f\n",temps_cpu);
  printf("temps_init-temps_final: %f\n" ,temps_initial-temps_final);
  if (aff==1){
    Grille_ferme_fenetre();

    Grille_free(&G);
  }
  for(i=0;i<dim;i++){
  	if(M[i]){
		free(M[i]);
	}
  }
  if(M)free(M);
  return 0;
}
