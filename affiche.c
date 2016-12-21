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
    init_graphics(LARGEUR_FENETRE,HAUTEUR_FENETRE);
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
    afficher_un_bouton(0,"JOUER", A.mode==JOUER);
    afficher_un_bouton(1,"SELECT",  A.mode==SELECT);
    afficher_un_bouton(2,"PREC",  A.mode==PREC);
    afficher_un_bouton(3,"SUIV",  A.mode==SUIV);
    afficher_un_bouton(4,"QUITTER",A.mode==QUITTER);
}



void afficher_sokoban(ACTION A,TABLEAU T) {
    fill_screen(noir);
    afficher_jeu(T);
    afficher_les_boutons(A);
    //affiche_all();
}


ACTION modifier_sudoku_action (ACTION A) {
 
    if (A.mode == JOUER) {
        A = resoudre_sokoban(A);
        return A; 
    }

    if (A.mode == SELECT) {
        return A; 
    }


    if (A.mode == PREC) {
        return A; 
    }
        

    if (A.mode == SUIV) {
        return A; 
    }   
    
    if (A.mode == QUITTER){
        return A;
    }

    return A;
    
}

void afficher_jeu(TABLEAU T) {
    
    POINT hg, bd;
    hg.x = 100; hg.y = 500;
    bd.x = hg.x+TAILLE_CASE_JEU; bd.y = hg.y+TAILLE_CASE_JEU;
    //draw_fill_rectangle(hg,bd,bleu);
    //draw_line(hg,bd,bleu);
    //graph_croix(hg,bd);
    
    int n, m;

    for(n=0;n<T.taille;n++) {
        hg.x = hg.x+TAILLE_CASE_JEU; bd.x = bd.x+TAILLE_CASE_JEU;
        hg.y = 500; bd.y = 525;
        for(m=0;m<T.taille;m++){
            hg.y = hg.y-TAILLE_CASE_JEU; bd.y = bd.y-TAILLE_CASE_JEU;

            if(T.array[n][m]==1)      //1 # mur
                draw_fill_rectangle(hg,bd,gris);
            if(T.array[n][m]==2)      //2 $ caisse
                draw_fill_rectangle(hg,bd,marron);
            if(T.array[n][m]==3)      //3 . objectif
                //draw_fill_rectangle(hg,bd,jaune);
                graph_croix(hg,bd);
            if(T.array[n][m]==4)      //4 @ homme
                draw_fill_rectangle(hg,bd,cyan);  
            
        }
    }
    
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

