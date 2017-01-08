// affiche.h du projet SOKOBAN
// Dang Thanh Duy 21607229  AKA BlackyStaar

#ifndef __AFFICHE_H
#define __AFFICHE_H

#include "constantes.h"
#include "jeu.h"
#include "action.h"

void initialiser_affichage() ;
TABLEAU selection_stage(int stage, TABLEAU t);
int tableau_chiffre(int caractere);
int tableau_chiffre_inverse(int caractere);

// A MODIFIER, POUR LES COULEURS DES BOUTONS
void afficher_un_bouton(int numero, char *texte, int la_selection);
void afficher_les_boutons(ACTION A);
void afficher_les_boutons_mode_creation(ACTION A);
void afficher_bouton_deplacement();
void afficher_lemode_de_creation_utilise(ACTION a);
void trait_en_dessous_lettre();
void trait_en_dessous_lettre_mode_creation();
void afficher_sokoban(ACTION A,TABLEAU T, int stage, int nb_move);
void afficher_mode_creation(ACTION A, TABLEAU T);
TABLEAU modifier_sudoku_action (ACTION A, TABLEAU t,int stage);
void afficher_victoire();

/************************************************************************/
//Affichage secondaire
void affichage_secondaire_mode_creation(ACTION a);
void affichage_secondaire_stage(int stage);
void affichage_secondaire_nb_move(int nb_move);

/************************************************************************/
//Limite du tableau sur l'interface graphique

void cadre_du_jeu();
void quadrillage();

/***************************************************************************/
//Affichage du tableau sur l'interface graphique

//void graph_croix(POINT haut_gauche,POINT bas_droit);
//void graph_homme(POINT haut_gauche);
//void graph_homme_objectif(POINT haut_gauche,POINT bas_droit);
void afficher_jeu(TABLEAU T);
 
#endif



