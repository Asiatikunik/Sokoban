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


TABLEAU initTab(TABLEAU t);
TABLEAU initTab_MUR(TABLEAU t);
void afficherTab(TABLEAU t);
ACTION resoudre_sokoban(ACTION A);
//POINT recup_pos_homme(TABLEAU T);
int nb_move(ACTION a,int nombre);
int modifier_stage(ACTION A, int stage);
int victoire(TABLEAU t);

/******************************************************************/
//Mode création

TABLEAU ajouter_mur(ACTION a, TABLEAU t);
//BOOL validation_des_ajout_bonhomme(TABLEAU t);
TABLEAU ajouter_tab_mode_creation(ACTION a, TABLEAU t);
TABLEAU ajout_tableau_creation(ACTION a, TABLEAU t);
TABLEAU retournee_tableau(TABLEAU t1);
void sauvegarde(TABLEAU t);

/******************************************************************/
//Utilisation des fonctions de liste

llist ajouter_deplacement_liste(ACTION a, llist ma_liste1, TABLEAU t);
llist ajouter_deplacement_liste_mode_creation(ACTION a, llist ma_liste1, TABLEAU t);

/*****************************************************************/
//LISTE

llist ajouter_debut(llist liste, TABLEAU tab);
llist ajouter_fin(llist liste, TABLEAU tab);
llist supprimerElement_debut(llist liste);
llist supprimerElement_Fin(llist liste);
llist supprimer_liste(llist liste);


/*****************************************************************/
//CONDITION DE DEPLACEMENT

// TABLEAU move_caisse_gauche(TABLEAU t, POINT homme);
// TABLEAU move_caisse_droite(TABLEAU t, POINT homme);
// TABLEAU move_caisse_haut(TABLEAU t, POINT homme);
// TABLEAU move_caisse_bas(TABLEAU t, POINT homme);
// TABLEAU move_goal_gauche(TABLEAU t, POINT homme);
// TABLEAU move_goal_droite(TABLEAU t, POINT homme);
// TABLEAU move_goal_haut(TABLEAU t, POINT homme);
// TABLEAU move_goal_bas(TABLEAU t, POINT homme);
// BOOL mouvement_valide_mur_gauche(TABLEAU t, POINT homme);
// BOOL mouvement_valide_mur_droite(TABLEAU t, POINT homme);
// BOOL mouvement_valide_mur_haut(TABLEAU t, POINT homme);
// BOOL mouvement_valide_mur_bas(TABLEAU t, POINT homme);
TABLEAU apres_clic_mouvement(TABLEAU t, ACTION a);	



#endif

