// affiche.c du projet SOKOBAN
// Dang Thanh Duy   AKA BlackyStaar

#include <stdio.h>
#include <stdlib.h>
#include <uvsqgraphics.h>
#include "constantes.h"
#include "jeu.h"
#include "affiche.h"
#include "action.h"

void initialiser_affichage() {
    init_graphics(LARGEUR_AFFICHAGE,HAUTEUR_AFFICHAGE);
    //affiche_auto_off();
}

TABLEAU selection_stage(int stage, TABLEAU t) {

    FILE* fichier = NULL;
    char caractereActuel = 0;
    int s, n=0, m=0;

    fichier = fopen("sasquatch1.xsb", "r");

    if(fichier != NULL) {
        for(s=-1; s<stage;s++){
            do {
                caractereActuel=fgetc(fichier);
                if(stage-1==s){
                    printf("%c", caractereActuel);
                    //t.array[n][m]=caractereActuel;    
                    t.array[n][m]=tableau_chiffe(caractereActuel);
                    n++;
                    if (caractereActuel=='\n'){
                        m++; 
                        n=0;
                    }
                }
            }while(caractereActuel != ';' && caractereActuel != EOF);         
        }
        fclose(fichier);
    }else
        printf("Impossible d'ouvrir le fichier des stages...\n");

    return t;
}



int tableau_chiffe(int caractere){

    if(caractere=='#')      //1 # mur
        return 1;
    if(caractere=='$')      //2 $ caisse
        return 2;
    if(caractere=='.')      //3 . objectif
        return 3;
    if(caractere=='@')      //4 @ homme
        return 4;   
   /* if (caractere=='\n')
        return '\n';*/
    if(caractere==' ')      
        return 5;

    return -2;
}

// A MODIFIER, POUR LES COULEURS DES BOUTONS
void afficher_un_bouton(int numero, char *texte, int la_selection) {
    // rouge si c'est le bouton actif et noir sinon
    COULEUR coul_texte = la_selection*rouge + (1 - la_selection)*noir;

    POINT bg, hd, centre;
    bg.x = numero*LARG_BOUTON; bg.y = HAUT_FENETRE-HAUT_BOUTON;
    hd.x = bg.x + LARG_BOUTON; hd.y = bg.y + HAUT_BOUTON;
    centre.x = (bg.x+hd.x)/2;  centre.y = (bg.y+hd.y)/2;

    draw_fill_rectangle(bg,hd,COUL_FOND);
    draw_rectangle(bg,hd,COUL_BORD);
    aff_pol_centre(texte,TAILLE_POLICE,centre,coul_texte);
}



void afficher_les_boutons(ACTION A) {
    // Le 3ème argument vaut 0 ou 1 selon que c'est le mode actif ou non
    afficher_un_bouton(0,"QUIT", A.mode==QUIT);
    afficher_un_bouton(1,"UNDO", A.mode==UNDO);
    afficher_un_bouton(2,"REDO", A.mode==REDO);
    afficher_un_bouton(3,"INIT", A.mode==INIT);
    afficher_un_bouton(4,"PRED", A.mode==PRED);
    afficher_un_bouton(5,"SUIV", A.mode==SUIV);
}


void affichage_secondaire(int stage){
    POINT p;
    p.x=30; p.y=600;
    aff_pol("stage=",12,p,blanc);
}



void afficher_sokoban(ACTION A,TABLEAU T, int stage) {
    fill_screen(noir);
    afficher_jeu(T);
    afficher_les_boutons(A);
    affichage_secondaire(stage);
    //affiche_all();
}


int modifier_stage(ACTION A, int stage){
    if (A.mode == PRED){
        if(stage!=1)
            stage--;
    }

    if (A.mode == SUIV){
        if(stage!=50)
            stage++; 
    }
    return stage;
}

TABLEAU modifier_sudoku_action (ACTION A, TABLEAU T,int stage) {
 
    if (A.mode == QUIT) {
        
        return T; 
    }

    if (A.mode == UNDO) {
        return T; 
    }


    if (A.mode == REDO) {
        return T; 
    }
        

    if (A.mode == INIT) {
        A = resoudre_sokoban(A);
        return T; 
    }   
    
    if (A.mode == PRED){
        T=selection_stage(stage, T ); 
        return T;
    }

    if (A.mode == SUIV){
        T=selection_stage(stage, T ); 
        return T;
    }
    return T;
    
}



void graph_croix(POINT haut_gauche,POINT bas_droit) {
    POINT haut_droit, bas_gauche;

    haut_droit.x = bas_droit.x; //hg.x=g.x+TAILLE_CASE_JEU;
    haut_droit.y = haut_gauche.y;

    bas_gauche.x = haut_gauche.x;
    bas_gauche.y = bas_droit.y;

    draw_line(haut_gauche,bas_droit,COUL_CROIX);
    draw_line(bas_gauche,haut_droit,COUL_CROIX); 
}

void afficher_jeu(TABLEAU T) {
    
    POINT hg, bd;
    hg.x = 20; hg.y = 400;
    bd.x = hg.x+TAILLE_CASE_JEU; bd.y = hg.y+TAILLE_CASE_JEU;
    //draw_fill_rectangle(hg,bd,bleu);
    //draw_line(hg,bd,bleu);
    //graph_croix(hg,bd);
    
    int n, m;

    for(n=0;n<T.taille;n++) {
        hg.x = hg.x+TAILLE_CASE_JEU; bd.x = bd.x+TAILLE_CASE_JEU;
        hg.y = 600; bd.y = 625;
        for(m=0;m<T.taille;m++){
            hg.y = hg.y-TAILLE_CASE_JEU; bd.y = bd.y-TAILLE_CASE_JEU;

            if(T.array[n][m]==1)      //1 # mur
                draw_fill_rectangle(hg,bd,gris);
            if(T.array[n][m]==2)      //2 $ caisse
                draw_fill_rectangle(hg,bd,marron);
            if(T.array[n][m]==3)      //3 . objectif
                //draw_fill_rectangle(hg,bd,jaune);
                graph_croix(hg,bd);
            if(T.array[n][m]==4){      //4 @ homme
                draw_fill_rectangle(hg,bd,cyan);  
                //POINT homme;
                //printf("x=%d y=%d \n\n",homme.x, homme.y);
            }
        }
    }
    
}




