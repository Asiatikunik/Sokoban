// main.c du projet SOKOBAN
// Dang Thanh Duy   AKA BlackyStaar

#include <stdio.h>
#include <stdlib.h>
//#include <uvsqgraphics.h>
#include "action.h"
#include "affiche.h"
#include "jeu.h"



int main(){

	TABLEAU t;
	ACTION a;
	int stage=1;

	a.mode=INIT;

	t=initTab(t);
	//afficherTab(t);
	t=selection_stage(stage, t);
	//afficherTab(t);

    initialiser_affichage();
    afficher_sokoban(a,t,stage); 

    do{
    	a = recuperer_action();
    	if (a.mode == PRED || a.mode == SUIV)
        	t=initTab(t);
    	stage=modifier_stage(a, stage); 
    	t = modifier_sudoku_action(a,t,stage); 
    	afficher_sokoban(a,t,stage);
    	//test(t);

    }while(mode_action(a)!=QUIT);

	//wait_escape();
    exit(0);
}
