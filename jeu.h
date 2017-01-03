// jeu.h du projet Sokoban
// Dang Thanh Duy 21607229  AKA BlackyStaar

#ifndef __JEU_H
#define __JEU_H

//#include <uvsqgraphics.h>
#include "constantes.h"
#include "action.h"

typedef struct sokoban SOKOBAN;
struct sokoban{
	TABLEAU t;
	int stage;
};

typedef struct tableau TABLEAU;
struct tableau {
	int taille;
	int array[100][100];
}; 

typedef struct element element;
struct element{
	TABLEAU azerty;
	int actuel;
	struct element *nxt;

};
typedef element* llist;


ACTION resoudre_sokoban(ACTION A);

TABLEAU initTab(TABLEAU tab);
void afficherTab(TABLEAU tab);

//TABLEAU apres_clic_mouvement(TABLEAU t, ACTION a);
TABLEAU apres_clic_mouvement(TABLEAU t, ACTION a);
int nb_move(ACTION a,int nombre);
//void test();

void init_sokoban();
SOKOBAN select_stage_sokoban(SOKOBAN s,int stage);

#endif