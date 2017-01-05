// jeu.h du projet Sokoban
// Dang Thanh Duy 21607229  AKA BlackyStaar

#ifndef __JEU_H
#define __JEU_H

//#include <uvsqgraphics.h>
#include "constantes.h"
#include "action.h"

typedef struct tableau TABLEAU;
struct tableau {
	int taille;
	int array[100][100];
	int move;
}; 

typedef struct element element;
struct element{
	TABLEAU azerty;
	//int move;
	struct element *nxt;
};
typedef element* llist;


ACTION resoudre_sokoban(ACTION A);
TABLEAU initTab(TABLEAU tab);
void afficherTab(TABLEAU tab);
TABLEAU apres_clic_mouvement(TABLEAU t, ACTION a);
int nb_move(ACTION a,int nombre);

//utilisation
llist ajouter_deplacement_liste(ACTION a, llist ma_liste1, TABLEAU t);
TABLEAU undo(TABLEAU t, llist ma_liste1, llist ma_liste2, int move);

//Liste
llist ajouter_debut(llist liste, TABLEAU tab);
llist ajouter_fin(llist liste, TABLEAU tab);
llist supprimerElement_debut(llist liste);
llist supprimerElement_Fin(llist liste);
//void supprimer_liste(llist liste);


#endif