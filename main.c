// main.c du projet SOKOBAN
// Dang Thanh Duy   AKA BlackyStaar

#include <stdio.h>
#include <stdlib.h>
#include "action.h"
#include "affiche.h"
#include "jeu.h"
//#include <uvsqgraphics.h>

int main(){

	TABLEAU t;
	ACTION a;
	a.mode=JOUER;

	t=initTab(t);
	//afficherTab(t);
	t=selection_stage(1, t);
	//afficherTab(t);

    initialiser_affichage();
    afficher_sokoban(a,t); 

    do{
    	a = recuperer_action();
    	afficher_sokoban(a,t);
    	a = modifier_sudoku_action (a); 

    }while(mode_action(a)!=QUITTER);

	//wait_escape();
    exit(0);
}
