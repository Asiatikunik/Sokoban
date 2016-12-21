// jeu.c du projet SOKOBAN
// Dang Thanh Duy   AKA BlackyStaar

#include <stdio.h>
#include <stdlib.h>
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
