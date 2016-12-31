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
			if(T.array[n][m]==4){ //Il y a une problème 
				P.x=n; P.y=m;		
				return P;
			}
			if(T.array[n][m]==6){ //je ne peux pas d'utilisé de "ou" "||"...
				P.x=n; P.y=m;
				return P;
			}
		}
	}

	P.x=0; P.y=0;
	return P;
}

/*****************************************************************/
//CONDITION DE DEPLACEMENT
/*
TABLEAU move_caisse_gauche(TABLEAU t, POINT p){

	return t;
}
*/

TABLEAU move_goal_gauche(TABLEAU t, POINT homme){
	
	if(t.array[homme.x][homme.y]==6 && t.array[homme.x-1][homme.y]==5){ //Sur objectif et case a cote rien
		t.array[homme.x][homme.y]=3; t.array[homme.x-1][homme.y]=4;
	}
	if (t.array[homme.x][homme.y]==6 && t.array[homme.x-1][homme.y]==3){ //Sur objectif et case a cote objectif
		t.array[homme.x][homme.y]=3; t.array[homme.x-1][homme.y]=6;
	}
	if(t.array[homme.x][homme.y]==4 && t.array[homme.x-1][homme.y]==3){ //Sur case vide et case a cote objectif
		t.array[homme.x][homme.y]=5; t.array[homme.x-1][homme.y]=6;
	}

	return t;
}

TABLEAU move_goal_droite(TABLEAU t, POINT homme){
	
	if(t.array[homme.x][homme.y]==6 && t.array[homme.x+1][homme.y]==5){ //Sur objectif et case a cote rien
		t.array[homme.x][homme.y]=3; t.array[homme.x+1][homme.y]=4;;
	} 
	if (t.array[homme.x][homme.y]==6 && t.array[homme.x+1][homme.y]==3){ //Sur objectif et case a cote objectif
		t.array[homme.x][homme.y]=3; t.array[homme.x+1][homme.y]=6;
	}
	if(t.array[homme.x][homme.y]==4 && t.array[homme.x+1][homme.y]==3){ //Sur case vide et case a cote objectif
		t.array[homme.x][homme.y]=5; t.array[homme.x+1][homme.y]=6;
	}
	return t;
}

TABLEAU move_goal_haut(TABLEAU t, POINT homme){
	
	if(t.array[homme.x][homme.y]==6 && t.array[homme.x][homme.y-1]==5){ //Sur objectif et case a cote rien
		t.array[homme.x][homme.y]=3; t.array[homme.x][homme.y-1]=4;;
	}
	if (t.array[homme.x][homme.y]==6 && t.array[homme.x][homme.y-1]==3){ //Sur objectif et case a cote objectif
		t.array[homme.x][homme.y]=3; t.array[homme.x][homme.y-1]=6;
	}
	if(t.array[homme.x][homme.y]==4 && t.array[homme.x][homme.y-1]==3){ //Sur case vide et case a cote objectif
		t.array[homme.x][homme.y]=5; t.array[homme.x][homme.y-1]=6;
	}
	return t;
}

TABLEAU move_goal_bas(TABLEAU t, POINT homme){
	
	if(t.array[homme.x][homme.y]==6 && t.array[homme.x][homme.y+1]==5){ //Sur objectif et case a cote rien
		t.array[homme.x][homme.y]=3; t.array[homme.x][homme.y+1]=4;;
	}
	
	if (t.array[homme.x][homme.y]==6 && t.array[homme.x][homme.y+1]==3){ //Sur objectif et case a cote objectif
		t.array[homme.x][homme.y]=3; t.array[homme.x][homme.y+1]=6;
	}
	if(t.array[homme.x][homme.y]==4 && t.array[homme.x][homme.y-1]==3){ //Sur case vide et case a cote objectif
		t.array[homme.x][homme.y]=5; t.array[homme.x][homme.y+1]=6;
	}
	return t;
}

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
			if(t.array[homme.x][homme.y]==4 && t.array[homme.x-1][homme.y]==5){  //mouvement normal
				t.array[homme.x][homme.y]=5; //cela ne sert a rien de separer en petit fonction
				t.array[homme.x-1][homme.y]=4;  //sa rajoutera des lignes pour rien	
			}else							
				t=move_goal_gauche(t,homme);	
		}
	}
	if(a.mode==DROITE){
		if(mouvement_valide_mur_droite(t,homme)==0){
			if(t.array[homme.x][homme.y]==4 && t.array[homme.x+1][homme.y]==5){
				t.array[homme.x][homme.y]=5;
				t.array[homme.x+1][homme.y]=4;
			}else
				t=move_goal_droite(t,homme);	
		}
	}
	if(a.mode==HAUT){
		if(mouvement_valide_mur_haut(t,homme)==0){
			if(t.array[homme.x][homme.y]==4 && t.array[homme.x][homme.y-1]==5){
				t.array[homme.x][homme.y]=5;
				t.array[homme.x][homme.y-1]=4;
			}else
				t=move_goal_haut(t,homme);
		}
	}
	if(a.mode==BAS){
		if(mouvement_valide_mur_bas(t,homme)==0){
			if(t.array[homme.x][homme.y]==4 && t.array[homme.x][homme.y+1]==5){
				t.array[homme.x][homme.y]=5;
				t.array[homme.x][homme.y+1]=4;
			}else
				t=move_goal_bas(t,homme);
		}
	}

	return t;
}


// 1 mur
// 2 caisse
// 3 objectif
// 4 homme
// 5 vide
// 6 homme sur objectif


