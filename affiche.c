// affiche.c du projet SOKOBAN
// Dang Thanh Duy 21607229  AKA BlackyStaar

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
    //fichier = fopen("test.txt", "r");

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
    afficher_un_bouton(0,"Quit", A.mode==QUIT);
    afficher_un_bouton(1,"Undo", A.mode==UNDO);
    afficher_un_bouton(2,"Redo", A.mode==REDO);
    afficher_un_bouton(3,"Init", A.mode==INIT);
    afficher_un_bouton(4,"Pred", A.mode==PRED);
    afficher_un_bouton(5,"Suiv", A.mode==SUIV);   
}

void afficher_bouton_deplacement(){
    POINT haut1, haut2, bas1, bas2, gauche1, gauche2, droite1, droite2;

    haut1.x=900; haut1.y=550;
    haut2.x=950; haut2.y=500;
    droite1.x=950; droite1.y=500;
    droite2.x=1000; droite2.y=450;
    bas1.x=900; bas1.y=450;
    bas2.x=950; bas2.y=400;
    gauche1.x=850; gauche1.y=500;
    gauche2.x=900; gauche2.y=450;

    draw_fill_rectangle(haut1,haut2,COUL_BOUTON);
    draw_fill_rectangle(droite1,droite2,COUL_BOUTON);
    draw_fill_rectangle(bas1,bas2,COUL_BOUTON);
    draw_fill_rectangle(gauche1,gauche2,COUL_BOUTON);
}


void affichage_secondaire_stage(int stage){
    POINT p1, p2;
    p1.x=30; p1.y=600; p2.x=80; p2.y=600;
    aff_pol("Stage=",12,p1,blanc);
    aff_int(stage,12,p2,blanc);
}

void affichage_secondaire_nb_move(int nb_move){
    POINT p1, p2;
    p1.x=100; p1.y=600; p2.x=145; p2.y=600;
    aff_pol("Move=",12,p1,blanc);
    aff_int(nb_move,12,p2,blanc);
}

void traie_en_dessous_lettre(){
    POINT p1, p2;
    p1.x=32; p1.y=610; p2.x=48; p2.y=610;
    draw_line(p1,p2,noir);
    p1.x=135; p1.y=610; p2.x=148; p2.y=610; 
    draw_line(p1,p2,noir);
    p1.x=243; p2.y=610; p2.x=258; p2.y=610; 
    draw_line(p1,p2,noir);
    p1.x=355; p2.y=610; p2.x=367; p2.y=610; 
    draw_line(p1,p2,noir);
    p1.x=460; p2.y=610; p2.x=472; p2.y=610; 
    draw_line(p1,p2,noir);
    p1.x=566; p2.y=610; p2.x=580; p2.y=610; 
    draw_line(p1,p2,noir);
}


void afficher_sokoban(ACTION A,TABLEAU T, int stage, int nb_move) {
    fill_screen(noir);
    afficher_jeu(T);
    afficher_les_boutons(A);
    afficher_bouton_deplacement();
    affichage_secondaire_stage(stage);
    traie_en_dessous_lettre();
    affichage_secondaire_nb_move(nb_move);
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
    POINT haut_droit, bas_gauche; //Bon, j'ai inversé en haut et en bas mais sa change rien

    haut_droit.x = bas_droit.x; //hg.x=g.x+TAILLE_CASE_JEU;
    haut_droit.y = haut_gauche.y;

    bas_gauche.x = haut_gauche.x;
    bas_gauche.y = bas_droit.y;

    draw_line(haut_gauche,bas_droit,COUL_CROIX);
    draw_line(bas_gauche,haut_droit,COUL_CROIX); 
    draw_line(haut_gauche,haut_droit,COUL_CROIX);
    draw_line(bas_gauche,bas_droit,COUL_CROIX);
    draw_line(haut_gauche,bas_gauche,COUL_CROIX);
    draw_line(haut_droit,bas_droit,COUL_CROIX);
}

void graph_homme(POINT haut_gauche){
    int rayon=TAILLE_CASE_JEU/2;
    haut_gauche.x=haut_gauche.x+(TAILLE_CASE_JEU/2);
    haut_gauche.y=haut_gauche.y+(TAILLE_CASE_JEU/2);
    draw_fill_circle(haut_gauche,rayon,cyan);
}

void graph_homme_objectif(POINT haut_gauche,POINT bas_droit){
    int rayon=TAILLE_CASE_JEU/2;
    graph_croix(haut_gauche,bas_droit);
    haut_gauche.x=haut_gauche.x+(TAILLE_CASE_JEU/2);
    haut_gauche.y=haut_gauche.y+(TAILLE_CASE_JEU/2);
    draw_fill_circle(haut_gauche,rayon,cyan);
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

            if(T.array[n][m]==MUR)      //1 # mur
                draw_fill_rectangle(hg,bd,gris);
            if(T.array[n][m]==CAISSE)      //2 $ caisse
                draw_fill_rectangle(hg,bd,marron);
            if(T.array[n][m]==OBJECTIF)      //3 . objectif
                //draw_fill_rectangle(hg,bd,jaune);
                graph_croix(hg,bd);
            if(T.array[n][m]==HOMME ){      //4 @ homme
                graph_homme(hg);  
                //POINT homme;
                //printf("x=%d y=%d \n\n",homme.x, homme.y);
            }
            if(T.array[n][m]==HOMME_OBJECTIF){    // ou 6 homme avec objectif en dessous
                graph_homme_objectif(hg,bd); 
            }
            if(T.array[n][m]==CAISSE_OBJECTIF){    // ou 7 caisse sur objectif
                draw_fill_rectangle(hg,bd,red); 
            }
        }
    }
    
}




