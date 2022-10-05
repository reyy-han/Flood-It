all: Flood-It_Partie1

API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
	gcc -c API_Gene_instance.c -lSDL

API_Grille.o: API_Grille.c API_Grille.h
	gcc -c API_Grille.c -lSDL

Liste_case.o: Liste_case.c Liste_case.h
	gcc -c Liste_case.c -lSDL

Fonctions_exo1.o: Fonctions_exo1.c Entete_Fonctions.h Liste_case.h
	gcc -c Fonctions_exo1.c -lSDL

S_Zsg.o: S_Zsg.c Entete_Fonctions.h S_Zsg.h
	gcc -c S_Zsg.c -lSDL

Fonctions_exo4.o: Fonctions_exo4.c Fonctions_exo4.h Entete_Fonctions.h
	gcc -c Fonctions_exo4.c -lSDL

Fonctions_exo5.o: Fonctions_exo5.c API_Grille.h Fonctions_exo5.h Fonctions_exo4.h
	gcc -c Fonctions_exo5.c -lSDL

Fonctions_exo6.o: Fonctions_exo6.c API_Grille.h Fonctions_exo6.h Fonctions_exo5.h
	gcc -c Fonctions_exo6.c -lSDL

Exo7.o: Exo7.c API_Grille.h Exo7.h Fonctions_exo6.h Fonctions_exo5.h Fonctions_exo4.h
	gcc -c Exo7.c -lSDL

Flood-It_Partie1.o: Flood-It_Partie1.c
	gcc -c Flood-It_Partie1.c -lSDL

Flood-It_Partie1: Flood-It_Partie1.o Liste_case.o  API_Grille.o API_Gene_instance.o Fonctions_exo1.o S_Zsg.o Fonctions_exo4.o Fonctions_exo5.o Fonctions_exo6.o Exo7.o
	gcc -g -ggdb -Wall -o Flood-It_Partie1 Flood-It_Partie1.o Liste_case.o API_Grille.o API_Gene_instance.o Fonctions_exo1.o S_Zsg.o Fonctions_exo4.o Fonctions_exo5.o Fonctions_exo6.o Exo7.o -lSDL

clean:
	rm -f *.o Flood-It_Partie1
