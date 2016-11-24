#include <uvsqgraphics.h>
#define TAILLE_POLICE 30

void initialiser_affichage() {
    init_graphics(600,400);
}

void lire_fichier(int stage) {

    FILE* fichier = NULL;
    int caractereActuel = 0, s;

    fichier = fopen("sasquatch1.xsb", "r");

    if(fichier != NULL) {
        for(s=-1; s<stage;s++){
                do {
                    caractereActuel=fgetc(fichier);
                        if(stage-1==s)
                            printf("%c", caractereActuel);     
                }while(caractereActuel != ';' && caractereActuel != EOF);         
        }
        fclose(fichier);
    }else{
        printf("Impossible d'ouvrir le fichier\n");
        return 1;
    }
    

}

int cree_tableau_jeu(){

    

}

void afficher_jeu(){

    wait_escape();

}


void ecrire_texte_dans_cercle(char *texte) {
    int rayon = 2 + largeur_texte(texte,TAILLE_POLICE)/2;
    POINT centre; centre.x = LARGEUR_FENETRE/2; 
    centre.y = HAUTEUR_FENETRE/2;
    POINT bas; bas.x = centre.x; bas.y = centre.y - 50;

    fill_screen(blanc);
    int i;
    char lenombre[4];
    
    for (i=0 ; i<=50 ; i++) {
        draw_fill_circle(centre,rayon,gold);
        if (i%2) aff_pol_centre(texte, TAILLE_POLICE, centre, red);
        sprintf(lenombre,"%d",50-i);
        aff_pol_centre(lenombre,TAILLE_POLICE+3*i,bas,red);
        attendre(100);
    }
}
void blackstar() {
    POINT P2, P3;
    COULEUR coul;
    coul = bleu;
    P2.x = 10; P2.y = 50;
    P3.x = 50; P3.y = 100;
    draw_fill_rectangle(P2, P3, coul);
    
    coul = jaune;
    int rayon = 25;
    draw_circle(P3, rayon, coul);
    
    wait_clic();
    draw_line(P2, P3, jaune);
    
    
    
    wait_escape();
    exit(0);

}

