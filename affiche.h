// affiche.h du projet SOKOBAN
// Dang Thanh Duy 21607229  AKA BlackyStaar

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
//int modifier_stage(ACTION A, int stage);


void afficher_sokoban(ACTION A,TABLEAU T,int stage, int nb_move);
void afficher_jeu(TABLEAU T);
void cadre_du_jeu();

void affichage_secondaire_mode_creation(ACTION a);
void afficher_les_boutons_mode_creation(ACTION A);
void quadrillage();
void afficher_mode_creation(ACTION A, TABLEAU T);
void afficher_bouton_deplacement();
void trait_en_dessous_lettre();
void trait_en_dessous_lettre_mode_creation();
void afficher_victoire();

#endif