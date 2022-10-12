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

- **1** - ***Inondation alétoire*** : Le choix de la couleur à inonder est déterminé de maniere aléatoire entre toutes les couleurs présentes dans la grille à l'initialisation de celle-ci.
- **3** - ***Inondation aléatoire adaptée*** : Comme pour la stratégie 1, on choisit aléatoirement la prochaine couleur, mais cette fois ci entre les couleurs toujours présentes sur la grille à l'instant t.
On utilise une nouvelle structure **S_Zsg**
- **4** - ***Transformation de la grille en graphe avec sommet*** (la grille n'est plus inonder par cases mais par groupe de cases qui sommet les sommets du graphe). Cette stratégie affiche les différents sommets créés.
- **5** - ***Inondation par sommet*** : On crée une nouvelle structure **bordure_graphe** qui correspond à la zone S_Zsg et sa bordure. On y retrouve la liste des sommets adjacents à la zone Zsg (deja inondée) et leur nombre de case. 
Ainsi, avec cette strategie on choisit la couleur qui correspond au sommet adjacent le plus grand.
- **6** - ***Chemin le plus court*** : La stratégie calcule d'abord le plus court chemin entre la case (0,0) (en haut à gauche) et la case (dim-1,dim-1) (en bas à droite). Elle inonde la grille en fonction de ce plus court chemin puis continue son inondation avec la stratégie 5.
- **7** - ***Inondation calculée*** : La méthode d’inondation est de choisir à chaque fois la couleur qui pourra engendrer le plus de cases inondées au coup d’après. 
On ne se contente pas d’une seule bordure comme dans max_bordure de l’exercice 5, mais de deux bordures. On peut voir cela comme un coup d’avance.
- **16 *(6+7)*** - : le mixte des stratégies 6 et 7



#### Evolution en miniature de la Grille :
       
![Capture_flood](https://user-images.githubusercontent.com/79942403/195354936-5b254ff9-1551-4846-887d-7b073ad26973.JPG)

L’inondation peut également être faite avec différentes stratégies comme le fait de choisir le voisin ayant le plus de cases à inonder ou encore choisir d’inonder la diagonale (en haut à gauche – en bas à droite) puis d’inonder en premier les voisins le plus judicieux.
