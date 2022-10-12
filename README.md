# Flood-It
Projet sur les Structures de données (L3) : Jeu d'inondation 'Flood-It'

## Description du Projet

Le projet porte sur l'implémentation d'un *jeu* d'inondation nommé **Flood It**.

Au début, on possède une grille de dimension quelconque, par exemple 5 x 5. Chacune de ses cases est coloriée par une couleur. 
La grille comporte un nombre limitée de couleur, par exemple 4.

le but est alors d'inonder la grille entièrement. Le jeu finit lorsque la grille n'a que des cases d'une seule couleur.
On part de la case (0,0), soit celle en haut à gauche.

L'inondation se comporte comme une boucle. A chaque nouveau tour, on inonde la grille avec une nouvelle couleur pour étendre la zone inondé de la grille.

Dans ce projet, le but est de développer plusieurs stratégies d'inondation afin de trouver la plus efficace:

#### Le code contient donc les stratégies :

- **1** - ***Inondation aléatoire*** : Le choix de la couleur à inonder est déterminé de manière aléatoire entre toutes les couleurs présentes dans la grille à l'initialisation de celle-ci.
- **3** - ***Inondation aléatoire adaptée*** : Comme pour la stratégie 1, on choisit aléatoirement la prochaine couleur, mais cette fois ci entre les couleurs toujours présentes sur la grille à l'instant t.

On utilise une nouvelle structure **S_Zsg**.

```c
Typedef struct s_Zsg {
  int dim;           /*dimension de la grille*/
  int nbcl;          /*nombre de couleurs*/
  ListeCase Lzsg;    /*Liste des cases de la zone Zsg*/
  ListeCase *B;      /*Tableau de listes de cases de la bordure*/
  int **App;         /*Tableau a double entree des appartenances*/
} S_Zsg;
```
- **4** - ***Transformation de la grille en graphe avec sommet*** (la grille n'est plus inonder par cases mais par groupe de cases qui sommet les sommets du graphe). Cette stratégie affiche les différents sommets créés.
- **5** - ***Inondation par sommet*** : On crée une nouvelle structure **bordure_graphe** qui correspond à la zone S_Zsg et sa bordure. On y retrouve la liste des sommets adjacents à la zone Zsg (déjà inondée) et leur nombre de case. 
Ainsi, avec cette stratégie on choisit la couleur qui correspond au sommet adjacent le plus grand.

```c
Typedef struct bordure_graphe ;
  int nbcl;
  Cellule_som * Lz;   /* Liste de pointeurs sur sommet de la zone Zsg */
  Cellule_som ** B;   /* Tableau de nbcl listes chainées de pointeurs sur sommet-zones de la bordure */
  int * taille;       /* Tableau des tailles de chaque liste de la bordure */
} Bordure_graphe;
```

- **6** - ***Chemin le plus court*** : La stratégie calcule d'abord le plus court chemin entre la case (0,0) (en haut à gauche) et la case (dim-1,dim-1) (en bas à droite). Elle inonde la grille en fonction de ce plus court chemin puis continue son inondation avec la stratégie 5.
- **7** - ***Inondation calculée*** : La méthode d’inondation est de choisir à chaque fois la couleur qui pourra engendrer le plus de cases inondées au coup d’après. 
On ne se contente pas d’une seule bordure comme dans max_bordure de l’exercice 5, mais de deux bordures. On peut voir cela comme un coup d’avance.

On utilise une nouvelle structure **Reste_graphe**:

```c
Typedef struct reste_graphe{
int nbcl;
Cellule_som ** SLz; /* Tableau de nbcl listes de pointeurs sur sommet de zone Zsg potentielles */
Cellule_som *** SB; /* Tableau de tableau de nbcl bordure chaque SB[i] correspond à la version i de Zsg
possible au prochain tour */
int ** Taille_SB;   /* Tableau de tableau de tailles des sous bordures */
int * taille_max;   /* Tableau des tailles max possible avec chaque version de Zsg possibles */
int *cl_max;        /* Tableau des numéros de couleur dans taille_max par versions */
} Reste_graphe;
```
- **16 *(6+7)*** - : le mixte des stratégies 6 et 7



#### Evolution en miniature de la Grille :
       
![Capture_flood](https://user-images.githubusercontent.com/79942403/195354936-5b254ff9-1551-4846-887d-7b073ad26973.JPG)


## Exécution

Pour lancer le jeu, il suffit de se placer dans le répertoire contenant tous les fichiers, puis de lancer les commandes:
```
$ make 
$ ./Flood-It_Partie1 <dimension> <nb_de_couleurs> <niveau_de_difficulte> <graine> <exo:0-1-3-4-5-6-7-13> <aff 0/1>
```


