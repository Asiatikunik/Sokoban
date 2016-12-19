// affiche.h du projet SOKOBAN
// Dang Thanh Duy   AKA BlackyStaar

#include "constantes.h"
#include "jeu.h"
#include "action.h"

#ifndef __AFFICHE_H
#define __AFFICHE_H

void initialiser_affichage();
TABLEAU selection_stage(int stage, TABLEAU t);
int cree_tableau_jeu();
int tableau_chiffe(int caractere);

void afficher_sokoban(ACTION A);

#endif