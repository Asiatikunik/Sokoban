// main.c du projet SOKOBAN
// Dang Thanh Duy 21607229  AKA BlackyStaar

#include <stdio.h>
#include <stdlib.h>
//#include <uvsqgraphics.h>
#include "action.h"
#include "affiche.h"
#include "jeu.h"

void mode_creation(){
    ACTION a;
    TABLEAU t;
    llist ma_liste3=NULL;
    llist ma_liste4=NULL;
        
    a.mode=100;
    t=initTab(t);
    afficher_mode_creation(a, t);
    do{
        a = recuperer_action_mode_creation(a);
        printf("MODEEEEEEEEEEEEEEE %d \n",a.mode);

        ma_liste3=ajouter_deplacement_liste_mode_creation(a, ma_liste3, t);

        if(a.mode == UNDO){
            if(ma_liste3!=NULL){
                ma_liste4=ajouter_debut(ma_liste4, t);
                t=ma_liste3->azerty;
                //ma_liste1=ma_liste1->nxt;
                element* temp = ma_liste3->nxt;
                free(ma_liste3);
                ma_liste3=temp;
            }    
        }

        if(a.mode == REDO){
            if(ma_liste4!=NULL){
                ma_liste3=ajouter_debut(ma_liste3, t);
                t=ma_liste4->azerty;
                //ma_liste2=ma_liste2->nxt;
                element* temp = ma_liste4->nxt;
                free(ma_liste4);
                ma_liste4=temp;
            }
        }
        if(a.mode==INIT){
            t=initTab(t);
            a.mode=ACTION_MUR;
        }
        if(a.mode==SAVE){
            sauvegarde(t);
        }
        afficher_mode_creation(a, t);
        t=ajout_tableau_creation(a, t);
        afficher_jeu(t);
    }while(mode_action(a)!=QUIT);
}

void mode_jeu(){

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
        printf("MODEEEEEEEEEEEEEEE %d \n",a.mode);

        if (a.mode == PRED || a.mode == SUIV) {
            t=initTab(t);
            stage=modifier_stage(a, stage);
            ma_liste1=supprimer_liste(ma_liste1);
            ma_liste2=supprimer_liste(ma_liste2);
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

        if(a.mode==CREA)
            mode_creation();

        //afficherListe(ma_liste1);
        t=apres_clic_mouvement(t,a);
        t = modifier_sudoku_action(a,t,stage); 
        t.move=nb_move(a,t.move);
        afficher_sokoban(a,t,stage,t.move);
        //printf("move= %d\n", ma_liste1->move);
        if(victoire(t)==1){
            afficher_victoire();
        }

    }while(mode_action(a)!=QUIT);
}

int main(int argc, char *argv[]){
      
    mode_jeu();

    //initialiser_affichage();
    //mode_creation();

	//wait_escape();
    exit(0);
}
