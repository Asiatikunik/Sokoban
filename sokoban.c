// main.c du projet SOKOBAN
// Dang Thanh Duy 21607229  AKA BlackyStaar

#include <stdio.h>
#include <stdlib.h>
//#include <uvsqgraphics.h>
#include "action.h"
#include "affiche.h"
#include "jeu.h"



int main(int argc, char *argv[]){
    
	TABLEAU t;
    //SOKOBAN s;
	ACTION a;
	int stage=1;
    int move=0;

    //s=init_sokoban();
	t=initTab(t);
	
	t=selection_stage(stage, t);


    initialiser_affichage();
    afficher_sokoban(a,t,stage,move); 

    do{
    	a = recuperer_action();
        //printf("MODEEEEEEEEEEEEEEE %d \n",a.mode);
    	if (a.mode == PRED || a.mode == SUIV) {
        	t=initTab(t);
            stage=modifier_stage(a, stage);
        }
        t=apres_clic_mouvement(t,a);
    	t = modifier_sudoku_action(a,t,stage); 
        move=nb_move(a,move);
    	afficher_sokoban(a,t,stage,move);

    }while(mode_action(a)!=QUIT);
    

	//wait_escape();
    exit(0);
}
