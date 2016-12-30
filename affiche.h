// affiche.h du projet SOKOBAN
// Dang Thanh Duy   AKA BlackyStaar

#ifndef __AFFICHE_H
#define __AFFICHE_H

#include "constantes.h"
#include "jeu.h"
#include "action.h"


void initialiser_affichage();
TABLEAU selection_stage(int stage, TABLEAU t);
int cree_tableau_jeu();
int tableau_chiffe(int caractere);
TABLEAU modifier_sudoku_action (ACTION A, TABLEAU T,int stage);
int modifier_stage(ACTION A, int stage);


void afficher_sokoban(ACTION A,TABLEAU T,int stage);
void afficher_jeu(TABLEAU T);



#endif