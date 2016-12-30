// jeu.h du projet Sokoban
// Dang Thanh Duy   AKA BlackyStaar

#ifndef __JEU_H
#define __JEU_H

//#include <uvsqgraphics.h>
#include "constantes.h"
#include "action.h"

struct tableau {
	int taille;
	int array[100][100];
}; 
typedef struct tableau TABLEAU;

ACTION resoudre_sokoban(ACTION A);

TABLEAU initTab(TABLEAU tab);
void afficherTab(TABLEAU tab);

//TABLEAU apres_clic_mouvement(TABLEAU t, ACTION a);
TABLEAU apres_clic_mouvement(TABLEAU t, ACTION a);
void test();

#endif