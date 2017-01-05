// main.c du projet SOKOBAN
// Dang Thanh Duy 21607229  AKA BlackyStaar

#include <stdio.h>
#include <stdlib.h>
//#include <uvsqgraphics.h>
#include "action.h"
#include "affiche.h"
#include "jeu.h"

int main(int argc, char *argv[]){
    
    
    //system("clear");
	TABLEAU t;
	ACTION a;
    llist ma_liste1=NULL;
    llist ma_liste2=NULL;
    //int move=0; 
    t.move=0;
    int stage=1;
    t=initTab(t);
    t=selection_stage(stage, t);

    initialiser_affichage();
    afficher_sokoban(a,t,stage,t.move); 
    
    do{
    	a = recuperer_action();
        //printf("MODEEEEEEEEEEEEEEE %d \n",a.mode);

    	if (a.mode == PRED || a.mode == SUIV) {
        	t=initTab(t);
            stage=modifier_stage(a, stage);
            //supprimer_liste(ma_liste1);
            //supprimer_liste(ma_liste2);
            //llist ma_liste1=NULL;
            //llist ma_liste2=NULL;
        }

        ma_liste1=ajouter_deplacement_liste(a, ma_liste1, t);

        if(a.mode == UNDO){
            if(ma_liste1!=NULL){
                ma_liste2=ajouter_debut(ma_liste2, t);
                t=ma_liste1->azerty;
                //ma_liste1=ma_liste1->nxt;
                element* temp = ma_liste1->nxt;
                free(ma_liste1);
                ma_liste1=temp;
            }    
        }

        if(a.mode == REDO){
            if(ma_liste2!=NULL){
                ma_liste1=ajouter_debut(ma_liste1, t);
                t=ma_liste2->azerty;
                //ma_liste2=ma_liste2->nxt;
                element* temp = ma_liste2->nxt;
                free(ma_liste2);
                ma_liste2=temp;
            }
        }

        
        if(a.mode==INIT){
            t=selection_stage(stage, t);
            t.move=0;
        }

        //afficherListe(ma_liste1);
        t=apres_clic_mouvement(t,a);
    	t = modifier_sudoku_action(a,t,stage); 
        t.move=nb_move(a,t.move);
    	afficher_sokoban(a,t,stage,t.move);
        //printf("move= %d\n", ma_liste1->move);

    }while(mode_action(a)!=QUIT);
    

	//wait_escape();
    exit(0);
}
