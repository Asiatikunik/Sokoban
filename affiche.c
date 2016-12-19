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
        return 7;
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

// Affiche un bouton
// numero donne le rang du bouton en les comptant à partir de la gauche et à partir de 0
// texte est le texte dans le bouton
// la_selection vaut 1 si c'est le mode actif et 0 sinon
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


// Affiche les 4 boutons
void afficher_les_boutons(ACTION A) {
    // Le 3ème argument vaut 0 ou 1 selon que c'est le mode actif ou non
    afficher_un_bouton(0,"SAISIR", A.mode==SAISIR);
    afficher_un_bouton(1,"JOUER",  A.mode==JOUER);
    afficher_un_bouton(2,"SOLVE",  A.mode==RESOUDRE);
    afficher_un_bouton(3,"QUITTER",A.mode==QUITTER);
}


// Affiche l'ensemble du sudoku
void afficher_sokoban(ACTION A) {
    fill_screen(noir);
    //afficher_grille();
    afficher_les_boutons(A);
    //affiche_all();
}