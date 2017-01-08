// jeu.c du projet SOKOBAN
// Dang Thanh Duy 21607229  AKA BlackyStaar

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

TABLEAU initTab_MUR(TABLEAU t) {
	int n,m;
	t.taille=TAILLE_TAB;
	for(n=0;n<t.taille; n++){
		for(m=0;m<t.taille; m++){
			t.array[n][m]=MUR;
		}
	}
	return t;	
}

void afficherTab(TABLEAU t) {

	int n,m;
	for(m=0; m<NB_CASE_ABSCISSE; m++){
		for(n=0; n<NB_CASE_ORDONNE; n++) {
			if(t.array[n][m]!=-1 || t.array[n][m]!=VIDE)
				printf("%d ",t.array[n][m]);
			if(t.array[n][m]==-1 || t.array[n][m]==VIDE)
		    	printf(" ");
		    else
				printf("%d ",t.array[n][m]);
		}
		printf("\n");
	}
}


ACTION resoudre_sokoban(ACTION A){
	return A;
}

POINT recup_pos_homme(TABLEAU T){
	POINT P;
	int n, m;

	for(n=0;n<T.taille;n++){
		for(m=0;m<T.taille;m++){
			if(T.array[n][m]==HOMME){ //Il y a une problème 
				P.x=n; P.y=m;		
				return P;
			}
			if(T.array[n][m]==HOMME_OBJECTIF){ //je ne peux pas d'utilisé de "ou" "||"...
				P.x=n; P.y=m;
				return P;
			}
		}
	}
	P.x=0; P.y=0;
	return P;
}

int nb_move(ACTION a,int nombre){
	if(a.mode==GAUCHE || a.mode==DROITE || a.mode==HAUT || a.mode==BAS)
		nombre++;
	if(a.mode==SUIV || a.mode==PRED)
		nombre=0;
	return nombre;
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

int victoire(TABLEAU t){
	int n,m;
	for(n=0;n<t.taille;n++){
		for(m=0;m<t.taille;m++){
			if(t.array[n][m]==OBJECTIF)
				return 0;
		}
	}
	return 1;
}

/******************************************************************/
//Mode création

TABLEAU ajouter_mur(ACTION a, TABLEAU t){

	int n, m, i, j;
	POINT haut_gauche;
	haut_gauche.x=50; haut_gauche.y=100;
	i=(a.x/TAILLE_CASE_JEU)-2; j=(a.y/TAILLE_CASE_JEU)+11;

	for(m=0; m<t.taille-1; m++){
		for(n=0; n<t.taille-1; n++){
			if(haut_gauche.x + (n*TAILLE_CASE_JEU) < a.x && 
				a.x < haut_gauche.x + ( (n+1)*TAILLE_CASE_JEU ) && 
				haut_gauche.y + (m*TAILLE_CASE_JEU) < a.y && 
				a.y < haut_gauche.y + ( (m+1)*TAILLE_CASE_JEU ) ){
				t.array[i][j]=MUR;
			}	
		}
	}	
	return t;
}

BOOL validation_des_ajout_bonhomme(TABLEAU t){
	int n,m,flag=0;
	POINT p; p.x=810; p.y=350;

    
	for(n = 0;n < t.taille; n++){
		for (m = 0; m < t.taille; m++){
			if(HOMME==t.array[n][m]){
				aff_pol("Il ne peut que avoir un homme",12,p,blanc);
				return flag=1;
			}
		}
	}
	return 0;
}

TABLEAU ajouter_tab_mode_creation(ACTION a, TABLEAU t){

	int n, m, i, j;
	POINT haut_gauche;
	haut_gauche.x=50; haut_gauche.y=100;
	i=(a.x/TAILLE_CASE_JEU)-2; j=(a.y/TAILLE_CASE_JEU)+11;
	int temp;

	if(a.mode==ACTION_MUR)
		temp=MUR;
	if(a.mode==ACTION_HOMME){
		temp=HOMME;
		if(validation_des_ajout_bonhomme(t)==1)
			temp=VIDE;
	}
	if(a.mode==ACTION_CAISSE)
		temp=CAISSE_OBJECTIF;
	if(a.mode==ACTION_OBJECTIF)
		temp=VIDE;

	for(m=0; m<t.taille-1; m++){
		for(n=0; n<t.taille-1; n++){
			if(haut_gauche.x + (n*TAILLE_CASE_JEU) < a.x && 
				a.x < haut_gauche.x + ( (n+1)*TAILLE_CASE_JEU ) && 
				haut_gauche.y + (m*TAILLE_CASE_JEU) < a.y && 
				a.y < haut_gauche.y + ( (m+1)*TAILLE_CASE_JEU ) ){
				if(i<30 && j<33)
					t.array[i][j]=temp;
			}	
		}
	}	

	return t;
}

TABLEAU ajout_tableau_creation(ACTION a, TABLEAU t){

	t=retournee_tableau(t);
	t=ajouter_tab_mode_creation(a,t);	
	t=retournee_tableau(t);

	return t;
}

TABLEAU retournee_tableau(TABLEAU t1){
	TABLEAU t2; int n,m,s=t1.taille;
	t2=initTab(t2);
	for(n=0;n<t1.taille;n++){
		s=t1.taille;
		for (m = 0; m < t2.taille; m++){
			s--;
			t2.array[n][s]=t1.array[n][m];
		}
	}
	return t2;
}

void sauvegarde(TABLEAU t){
	FILE* fichier = NULL;
	int n,m;
	//int temp;

    fichier = fopen("sauvegarde.xsb", "w");

    if(fichier != NULL) {
    	fputc(';',fichier);fputc('\n',fichier);fputc('\n',fichier);
		for(m=0; m<NB_CASE_ABSCISSE; m++){
			for(n=0; n<NB_CASE_ORDONNE; n++) {
				//temp=tableau_chiffre_inverse(t.array[n][m]);
				//fprintf(fichier, "%d", temp);
				fprintf(fichier, "%d ", t.array[n][m]);
    		}
    		fputc('\n',fichier);
    	}
    	fputc('\n',fichier);fputc(';',fichier);fputc('\n',fichier);
        //fclose(fichier);
    }

}
/******************************************************************/
//Utilisation des fonctions de liste

llist ajouter_deplacement_liste(ACTION a, llist ma_liste1, TABLEAU t){
	if(a.mode==GAUCHE || a.mode==DROITE || a.mode==HAUT || a.mode==BAS || a.mode==INIT)
		ma_liste1=ajouter_debut(ma_liste1,t);
	return ma_liste1;
}

llist ajouter_deplacement_liste_mode_creation(ACTION a, llist ma_liste1, TABLEAU t){
	if(a.mode==ACTION_OBJECTIF || a.mode==ACTION_CAISSE 
		|| a.mode==ACTION_HOMME|| a.mode==ACTION_MUR)
		ma_liste1=ajouter_debut(ma_liste1,t);
	return ma_liste1;
}

/*
TABLEAU undo(TABLEAU t, llist ma_liste1, llist ma_liste2, int move){
	if(move != 0){
		ma_liste2=ajouter_debut(ma_liste2,t);
		ma_liste1=supprimerElement_debut(ma_liste1);
		//move--;
		return ma_liste1->azerty;
	}
	
	if(move == 0){
		return t;
	}
	return t;
}
*/

/*
TABLEAU undo(TABLEAU t, llist ma_liste1, llist ma_liste2, int move){
	if(move != 0){
		ma_liste2=ajouter_debut(ma_liste2,t);
		//ma_liste1=supprimerElement_debut(ma_liste1);
		return supprimerElement_debut(ma_liste1);
	}
	if(move == 0){
		return t;
	}
	return t;
}
*/



/*****************************************************************/
//LISTE

llist ajouter_debut(llist liste, TABLEAU tab){
	element* nouvelElement= malloc(sizeof(element));
	nouvelElement->azerty=tab;
	nouvelElement->nxt=liste;
	return nouvelElement;
}

llist ajouter_fin(llist liste, TABLEAU tab){
	element* nouvelElement= malloc(sizeof(element));
	nouvelElement->azerty=tab;
	nouvelElement->nxt=NULL;

	if(liste==NULL){
		return nouvelElement;
	}else{
		element* temp=liste;
		while(temp->nxt !=NULL){
			temp=temp->nxt;
		}
		temp->nxt=nouvelElement;
	}
	return liste;
}

llist supprimerElement_debut(llist liste){
	if(liste != NULL){
		element* aRenvoyer = liste->nxt;
		free(liste);
		return aRenvoyer;
	}else{
		return NULL;
	}
}

llist supprimerElement_Fin(llist liste){

    if(liste == NULL)
		return NULL;

    if(liste->nxt == NULL){
        free(liste);
        return NULL;
    }

    element* tmp = liste;
    element* ptmp = liste;

    while(tmp->nxt != NULL){
        ptmp = tmp;
        tmp = tmp->nxt;
    }

    ptmp->nxt = NULL;
    free(tmp);
   	return liste;
}

llist supprimer_liste(llist liste){
	while(liste!=NULL){
		liste=supprimerElement_debut(liste);
	}
	return liste;
}


/*****************************************************************/
//CONDITION DE DEPLACEMENT

TABLEAU move_caisse_gauche(TABLEAU t, POINT homme){
	if(t.array[homme.x-1][homme.y]==CAISSE && t.array[homme.x-2][homme.y]==VIDE){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x-1][homme.y]=HOMME;
		t.array[homme.x-2][homme.y]=CAISSE;
	}
	return t;
}
TABLEAU move_caisse_droite(TABLEAU t, POINT homme){
	if(t.array[homme.x+1][homme.y]==CAISSE && t.array[homme.x+2][homme.y]==VIDE){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x+1][homme.y]=HOMME;
		t.array[homme.x+2][homme.y]=CAISSE;
	}
	return t;
}
TABLEAU move_caisse_haut(TABLEAU t, POINT homme){
	if(t.array[homme.x][homme.y-1]==CAISSE && t.array[homme.x][homme.y-2]==VIDE){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x][homme.y-1]=HOMME;
		t.array[homme.x][homme.y-2]=CAISSE;
	}
	return t;
}
TABLEAU move_caisse_bas(TABLEAU t, POINT homme){
	if(t.array[homme.x][homme.y+1]==CAISSE && t.array[homme.x][homme.y+2]==VIDE){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x][homme.y+1]=HOMME;
		t.array[homme.x][homme.y+2]=CAISSE;
	}
	return t;
}

TABLEAU move_goal_gauche(TABLEAU t, POINT homme){
	
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x-1][homme.y]==VIDE){ //Sur objectif et case a cote rien
		t.array[homme.x][homme.y]=OBJECTIF; t.array[homme.x-1][homme.y]=HOMME;
	}
	if (t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x-1][homme.y]==OBJECTIF){ //Sur objectif et case a cote objectif
		t.array[homme.x][homme.y]=OBJECTIF; t.array[homme.x-1][homme.y]=HOMME_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x-1][homme.y]==OBJECTIF){ //Sur case vide et case a cote objectif
		t.array[homme.x][homme.y]=VIDE; t.array[homme.x-1][homme.y]=HOMME_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x-1][homme.y]==CAISSE 
		&& t.array[homme.x-2][homme.y]==OBJECTIF){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x-1][homme.y]=HOMME;
		t.array[homme.x-2][homme.y]=CAISSE_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x-1][homme.y]==CAISSE_OBJECTIF 
		&& t.array[homme.x-2][homme.y]==VIDE){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x-1][homme.y]=HOMME_OBJECTIF;
		t.array[homme.x-2][homme.y]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x-1][homme.y]==CAISSE_OBJECTIF 
		&& t.array[homme.x-2][homme.y]==VIDE){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x-1][homme.y]=HOMME_OBJECTIF;
		t.array[homme.x-2][homme.y]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x-1][homme.y]==CAISSE_OBJECTIF
		&& t.array[homme.x-2][homme.y]==OBJECTIF){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x-1][homme.y]=HOMME_OBJECTIF;
		t.array[homme.x-2][homme.y]=CAISSE_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x-1][homme.y]==CAISSE
		&& t.array[homme.x-2][homme.y]==VIDE){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x-1][homme.y]=HOMME;
		t.array[homme.x-2][homme.y]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x-1][homme.y]==CAISSE
		&& t.array[homme.x-2][homme.y]==OBJECTIF){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x-1][homme.y]=HOMME;
		t.array[homme.x-2][homme.y]=CAISSE_OBJECTIF;
	}
	return t;
}

TABLEAU move_goal_droite(TABLEAU t, POINT homme){
	
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x+1][homme.y]==VIDE){ //Sur objectif et case a cote rien
		t.array[homme.x][homme.y]=OBJECTIF; t.array[homme.x+1][homme.y]=HOMME;;
	} 
	if (t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x+1][homme.y]==OBJECTIF){ //Sur objectif et case a cote objectif
		t.array[homme.x][homme.y]=OBJECTIF; t.array[homme.x+1][homme.y]=HOMME_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x+1][homme.y]==OBJECTIF){ //Sur case vide et case a cote objectif
		t.array[homme.x][homme.y]=VIDE; t.array[homme.x+1][homme.y]=HOMME_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x+1][homme.y]==CAISSE 
		&& t.array[homme.x+2][homme.y]==OBJECTIF){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x+1][homme.y]=HOMME;
		t.array[homme.x+2][homme.y]=CAISSE_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x+1][homme.y]==CAISSE_OBJECTIF 
		&& t.array[homme.x+2][homme.y]==VIDE){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x+1][homme.y]=HOMME_OBJECTIF;
		t.array[homme.x+2][homme.y]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x+1][homme.y]==CAISSE_OBJECTIF 
		&& t.array[homme.x+2][homme.y]==VIDE){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x+1][homme.y]=HOMME_OBJECTIF;
		t.array[homme.x+2][homme.y]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x+1][homme.y]==CAISSE_OBJECTIF
		&& t.array[homme.x+2][homme.y]==OBJECTIF){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x+1][homme.y]=HOMME_OBJECTIF;
		t.array[homme.x+2][homme.y]=CAISSE_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x+1][homme.y]==CAISSE
		&& t.array[homme.x+2][homme.y]==VIDE){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x+1][homme.y]=HOMME;
		t.array[homme.x+2][homme.y]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x+1][homme.y]==CAISSE
		&& t.array[homme.x+2][homme.y]==OBJECTIF){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x+1][homme.y]=HOMME;
		t.array[homme.x+2][homme.y]=CAISSE_OBJECTIF;
	}
	return t;
}

TABLEAU move_goal_haut(TABLEAU t, POINT homme){
	
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x][homme.y-1]==VIDE){ //Sur objectif et case a cote rien
		t.array[homme.x][homme.y]=OBJECTIF; t.array[homme.x][homme.y-1]=HOMME;;
	}
	if (t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x][homme.y-1]==OBJECTIF){ //Sur objectif et case a cote objectif
		t.array[homme.x][homme.y]=OBJECTIF; t.array[homme.x][homme.y-1]=HOMME_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x][homme.y-1]==OBJECTIF){ //Sur case vide et case a cote objectif
		t.array[homme.x][homme.y]=VIDE; t.array[homme.x][homme.y-1]=HOMME_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x][homme.y-1]==CAISSE 
		&& t.array[homme.x][homme.y-2]==OBJECTIF){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x][homme.y-1]=HOMME;
		t.array[homme.x][homme.y-2]=CAISSE_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x][homme.y-1]==CAISSE_OBJECTIF 
		&& t.array[homme.x][homme.y-2]==VIDE){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x][homme.y-1]=HOMME_OBJECTIF;
		t.array[homme.x][homme.y-2]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x][homme.y-1]==CAISSE_OBJECTIF 
		&& t.array[homme.x][homme.y-2]==VIDE){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x][homme.y-1]=HOMME_OBJECTIF;
		t.array[homme.x][homme.y-2]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x][homme.y-1]==CAISSE_OBJECTIF
		&& t.array[homme.x][homme.y-2]==OBJECTIF){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x][homme.y-1]=HOMME_OBJECTIF;
		t.array[homme.x][homme.y-2]=CAISSE_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x][homme.y-1]==CAISSE
		&& t.array[homme.x][homme.y-2]==VIDE){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x][homme.y-1]=HOMME;
		t.array[homme.x][homme.y-2]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x][homme.y-1]==CAISSE
		&& t.array[homme.x][homme.y-2]==OBJECTIF){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x][homme.y-1]=HOMME;
		t.array[homme.x][homme.y-2]=CAISSE_OBJECTIF;
	}
	return t;
}

TABLEAU move_goal_bas(TABLEAU t, POINT homme){
	
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x][homme.y+1]==VIDE){ //Sur objectif et case a cote rien
		t.array[homme.x][homme.y]=OBJECTIF; t.array[homme.x][homme.y+1]=HOMME;;
	}
	
	if (t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x][homme.y+1]==OBJECTIF){ //Sur objectif et case a cote objectif
		t.array[homme.x][homme.y]=OBJECTIF; t.array[homme.x][homme.y+1]=HOMME_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x][homme.y+1]==OBJECTIF){ //Sur case vide et case a cote objectif
		t.array[homme.x][homme.y]=VIDE; t.array[homme.x][homme.y+1]=HOMME_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x][homme.y+1]==CAISSE 
		&& t.array[homme.x][homme.y+2]==OBJECTIF){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x][homme.y+1]=HOMME;
		t.array[homme.x][homme.y+2]=CAISSE_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x][homme.y+1]==CAISSE_OBJECTIF 
		&& t.array[homme.x][homme.y+2]==VIDE){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x][homme.y+1]=HOMME_OBJECTIF;
		t.array[homme.x][homme.y+2]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x][homme.y+1]==CAISSE_OBJECTIF 
		&& t.array[homme.x][homme.y+2]==VIDE){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x][homme.y+1]=HOMME_OBJECTIF;
		t.array[homme.x][homme.y+2]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x][homme.y+1]==CAISSE_OBJECTIF
		&& t.array[homme.x][homme.y+2]==OBJECTIF){
		t.array[homme.x][homme.y]=VIDE;
		t.array[homme.x][homme.y+1]=HOMME_OBJECTIF;
		t.array[homme.x][homme.y+2]=CAISSE_OBJECTIF;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x][homme.y+1]==CAISSE
		&& t.array[homme.x][homme.y+2]==VIDE){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x][homme.y+1]=HOMME;
		t.array[homme.x][homme.y+2]=CAISSE;
	}
	if(t.array[homme.x][homme.y]==HOMME_OBJECTIF && t.array[homme.x][homme.y+1]==CAISSE
		&& t.array[homme.x][homme.y+2]==OBJECTIF){
		t.array[homme.x][homme.y]=OBJECTIF;
		t.array[homme.x][homme.y+1]=HOMME;
		t.array[homme.x][homme.y+2]=CAISSE_OBJECTIF;
	}
	return t;
}

BOOL mouvement_valide_mur_gauche(TABLEAU t, POINT homme){
	if(t.array[homme.x-1][homme.y]!=MUR)
		return 0;
	return 1;
}
BOOL mouvement_valide_mur_droite(TABLEAU t, POINT homme){
	if(t.array[homme.x+1][homme.y]!=MUR)
		return 0;
	return 1;
}
BOOL mouvement_valide_mur_haut(TABLEAU t, POINT homme){
	if(t.array[homme.x][homme.y-1]!=MUR)
		return 0;
	return 1;
}
BOOL mouvement_valide_mur_bas(TABLEAU t, POINT homme){
	if(t.array[homme.x][homme.y+1]!=MUR)
		return 0;	
	return 1;
}

TABLEAU apres_clic_mouvement(TABLEAU t, ACTION a){ //Si HOMME_OBJECTIF alors bonhomme avec objectif dessous
	POINT homme=recup_pos_homme(t);
	if(a.mode==GAUCHE){
		if(mouvement_valide_mur_gauche(t,homme)==0){
			if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x-1][homme.y]==VIDE){  //mouvement normal
				t.array[homme.x][homme.y]=VIDE; //cela ne sert a rien de separer en petit fonction
				t.array[homme.x-1][homme.y]=HOMME;  //sa rajoutera des lignes pour rien	
			}else{							
				t=move_goal_gauche(t,homme);	
				t=move_caisse_gauche(t, homme);
			}
		}
	}
	if(a.mode==DROITE){
		if(mouvement_valide_mur_droite(t,homme)==0){
			if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x+1][homme.y]==VIDE){
				t.array[homme.x][homme.y]=VIDE;
				t.array[homme.x+1][homme.y]=HOMME;
			}else{
				t=move_goal_droite(t,homme);
				t=move_caisse_droite(t, homme);	
			}
		}
	}
	if(a.mode==HAUT){
		if(mouvement_valide_mur_haut(t,homme)==0){
			if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x][homme.y-1]==VIDE){
				t.array[homme.x][homme.y]=VIDE;
				t.array[homme.x][homme.y-1]=HOMME;
			}else{
				t=move_goal_haut(t,homme);
				t=move_caisse_haut(t, homme);
			}
		}
	}
	if(a.mode==BAS){
		if(mouvement_valide_mur_bas(t,homme)==0){
			if(t.array[homme.x][homme.y]==HOMME && t.array[homme.x][homme.y+1]==VIDE){
				t.array[homme.x][homme.y]=VIDE;
				t.array[homme.x][homme.y+1]=HOMME;
			}else{
				t=move_goal_bas(t,homme);
				t=move_caisse_bas(t, homme);
			}
		}
	}

	return t;
}



