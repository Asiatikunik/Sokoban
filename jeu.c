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


POINT recuperer_pos_homme(TABLEAU T){
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


void test(TABLEAU T){
	POINT homme;
	homme=recuperer_pos_homme(T);
    printf("x=%d y=%d \n\n",homme.x, homme.y);
}


