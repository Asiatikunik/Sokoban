// jeu.h du projet Sokoban
// Dang Thanh Duy   AKA BlackyStaar

#include "constantes.h"
#include "action.h"

#ifndef __JEU_H
#define __JEU_H

struct tableau {
	int taille;
	int array[100][100];
}; 
typedef struct tableau TABLEAU;

ACTION resoudre_sokoban(ACTION A);

TABLEAU initTab(TABLEAU tab);
void afficherTab(TABLEAU tab);

#endif