// jeu.c du projet SOKOBAN
// Dang Thanh Duy   AKA BlackyStaar

#include <stdio.h>
#include <stdlib.h>
#include <uvsqgraphics.h>
#include "jeu.h"
#include "constantes.h"
#include "action.h"



TABLEAU initTab(TABLEAU t) {
	int n,m;
	t.taille=TAILLE_TAB;
	for(n=0;n<t.taille; n++){
		for(m=0;m<t.taille; m++){
			t.array[n][m]=-1;
		}
	}

	return t;	
}

void afficherTab(TABLEAU t) {

	int n,m;
	for(n=0; n<t.taille; n++){
		for(m=0; m<t.taille; m++) {
			if(t.array[n][m]!=-1 || t.array[n][m]!=5)
				printf("%d ",t.array[n][m]);
			if(t.array[n][m]==-1 || t.array[n][m]==5)
		    	printf(" ");
		    else
				printf("%d ",t.array[n][m]);
		}
		printf("\n");
	}
}

/*
void afficherTab2(TABLEAU t){

	int n,m;
	for(n=0; n<t.taille; n++) {
		for(m=0; m<t.taille; m++) {  
			if(t.array[n][m]==1)      //1 # mur
		        printf("#");
		    if(t.array[n][m]==2)      //2 $ caisse
		        printf("$");
		    if(t.array[n][m]==3)      //3 . objectif
		        printf(".");
		    if(t.array[n][m]==4)      //4 @ homme
		        printf("@");
		    if(t.array[n][m]==-1 || t.array[n][m]==5)
		    	printf(" ");
		    else
				printf("%d ",t.array[n][m]);
		}
		printf("\n");
	}
 
}*/

ACTION resoudre_sokoban(ACTION A){
	return A;
	}

POINT recup_pos_homme(TABLEAU T){
	POINT P;
	int n, m;

	for(n=0;n<T.taille;n++){
		for(m=0;m<T.taille;m++){
			if(T.array[n][m]==4){
				P.x=n; P.y=m;
				return P;
			}
		}
	}

	P.x=0; P.y=0;
	return P;
}


//CONDITION DE DEPLACEMENT

/*
TABLEAU move_goal_gauche(TABLEAU t, POINT homme){
	if(t.array[homme.x][homme.y]==6 && t.array[homme.x-1][homme.y]==5){ //Sur objectif et case a cote rien
		t.array[homme.x][homme.y]=3;
		t.array[homme.x-1][homme.y]=4;
	}else if (t.array[homme.x][homme.y]==6 && t.array[homme.x-1][homme.y]==3){ //Sur objectif et case a cote objectif
		t.array[homme.x][homme.y]=3;
		t.array[homme.x-1][homme.y]=6;
	}else if(t.array[homme.x][homme.y]=4 && t.array[homme.x-1][homme.y]==3){ //Sur case vide et case a cote objectif
		t.array[homme.x][homme.y]=5;
		t.array[homme.x-1][homme.y]=6;
	}else{
		t.array[homme.x][homme.y]=5;
		t.array[homme.x-1][homme.y]=4;
	}

	return t;
}
*/

BOOL mouvement_valide_mur_gauche(TABLEAU t, POINT homme){
	if(t.array[homme.x-1][homme.y]!=1)
		return 0;
	return 1;
}
BOOL mouvement_valide_mur_droite(TABLEAU t, POINT homme){
	if(t.array[homme.x+1][homme.y]!=1)
		return 0;
	return 1;
}
BOOL mouvement_valide_mur_haut(TABLEAU t, POINT homme){
	if(t.array[homme.x][homme.y-1]!=1)
		return 0;
	return 1;
}
BOOL mouvement_valide_mur_bas(TABLEAU t, POINT homme){
	if(t.array[homme.x][homme.y+1]!=1)
		return 0;	
	return 1;
}

TABLEAU apres_clic_mouvement(TABLEAU t, ACTION a){ //Si 6 alors bonhomme avec objectif dessous
	POINT homme=recup_pos_homme(t);
	if(a.mode==GAUCHE){
		if(mouvement_valide_mur_gauche(t,homme)==0){
			//t=move_goal_gauche(t,homme);
			t.array[homme.x][homme.y]=5;
			t.array[homme.x-1][homme.y]=4;
		}
	}
	if(a.mode==DROITE){
		if(mouvement_valide_mur_droite(t,homme)==0){
			//t=move_goal_gauche(t,homme);
			t.array[homme.x][homme.y]=5;
			t.array[homme.x+1][homme.y]=4;
		}
	}
	if(a.mode==HAUT){
		if(mouvement_valide_mur_haut(t,homme)==0){
			//t=move_goal_gauche(t,homme);
			t.array[homme.x][homme.y]=5;
			t.array[homme.x][homme.y-1]=4;
		}
	}
	if(a.mode==BAS){
		if(mouvement_valide_mur_bas(t,homme)==0){
			//t=move_goal_gauche(t,homme);
			t.array[homme.x][homme.y]=5;
			t.array[homme.x][homme.y+1]=4;
		}
	}

	return t;
}



/*
    if(caractere=='#')      //1 # mur
        return 1;
    if(caractere=='$')      //2 $ caisse
        return 2;
    if(caractere=='.')      //3 . objectif
        return 3;
    if(caractere=='@')      //4 @ homme
        return 4;   
    if(caractere==' ')      
        return 5;
*/


/*
void test(TABLEAU T){
	POINT homme;
	homme=recuperer_pos_homme(T);
    printf("x=%d y=%d \n\n",homme.x, homme.y);
}*/


