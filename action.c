// action.h du projet SOKOBAN
// Dang Thanh Duy 21607229  AKA BlackyStaar

#include <stdio.h>
#include <stdlib.h>
#include <uvsqgraphics.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "action.h"
#include "constantes.h"
#include "jeu.h"

#ifndef ___wait_key_or_clic
#define ___wait_key_or_clic
POINT wait_key_or_clic(char* isKey){
  	int encore = 1;
	POINT dep;
	SDL_Event event;
	*isKey = 1;
	dep.x = 0;
	dep.y = 0;
	while (encore && SDL_WaitEvent(&event))
	  {
	    /* Si l'utilisateur a appuyé sur une touche */
	    if (event.type == SDL_KEYDOWN)
	      {
		if(event.key.keysym.sym == SDLK_ESCAPE) exit(0);
		else if(event.key.keysym.sym == SDLK_LEFT)  encore=0, (dep.x) = -1;
		else if(event.key.keysym.sym == SDLK_RIGHT) encore=0, (dep.x) = 1;
		else if(event.key.keysym.sym == SDLK_UP)    encore=0, (dep.y) = 1;
		else if(event.key.keysym.sym == SDLK_DOWN)  encore=0, (dep.y) = -1;
		else if(256 <= event.key.keysym.sym && event.key.keysym.sym <= 265) encore=0, *isKey = '0' + event.key.keysym.sym - 256;
		else if('a' <= event.key.keysym.sym && event.key.keysym.sym <= 'z') encore=0,  *isKey = event.key.keysym.sym;
		else *isKey = 0;
		while (SDL_WaitEvent(&event)){
		  if (event.type == SDL_KEYUP) break;
		}
	      }
	    /* Si l'utilisateur clique avec la souris */
	    else if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
	      {
		*isKey = 0;
		encore = 0;
		dep.x = event.button.x;
		dep.y = HEIGHT-event.button.y;
	      }
	    /* Si l'utilisateur a demandé à fermer la fenêtre, on quitte */
	    else if (event.type == SDL_QUIT) exit(0);
	  }
	return dep;
}
#endif


ACTION recuperer_action() {
	ACTION A; POINT P; char c;
	P.x=0; P.y=0;

	do{	
		P=wait_key_or_clic(&c);
		//P=wait_clic();
		if ((P.x < 1*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='q') { A.mode = QUIT; return A; }
		else if ((P.x < 2*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='u') { A.mode = UNDO; return A; }
		else if ((P.x < 3*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='r') { A.mode = REDO; return A; }
		else if ((P.x < 4*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='i') { A.mode = INIT; return A; }
		else if ((P.x < 5*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='p') { A.mode = PRED; return A; } 
		else if ((P.x < 6*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='s') { A.mode = SUIV; return A; } 
		else if ((850<P.x && P.x<900 && 450<P.y && P.y<500) || P.x==-1) { A.mode = GAUCHE; return A; } 
		else if ((950<P.x && P.x<1000 && 450<P.y && P.y<500) || P.x==1) { A.mode = DROITE; return A; }
		else if ((900<P.x && P.x<950 && 500<P.y && P.y<550) || P.y==1) { A.mode = HAUT; return A; }
		else if ((900<P.x && P.x<950 && 400<P.y && P.y<450) || P.y==-1) { A.mode = BAS; return A; }
		else if ((P.x < 7*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='c') { A.mode = CREA; return A; }
		else {A.mode = RIEN; }

	}while(1);

	return A;
}

int mode_action(ACTION A) {
	return A.mode;
} 

ACTION recuperer_action_mode_creation(ACTION A) {
	POINT P; char c;
	P.x=0; P.y=0;

	do{	
		P=wait_key_or_clic(&c);
		//P=wait_clic();
		A.x=P.x;
		A.y=P.y;
		if ((P.x < 1*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='q') { A.mode = QUIT; return A; }
		else if ((P.x < 2*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='i') { A.mode = INIT; return A; }
		else if ((P.x < 3*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='u') { A.mode = UNDO; return A; } 
		else if ((P.x < 4*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='r') { A.mode = REDO; return A; }
		else if ((P.x < 5*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='s') { A.mode = SAVE; return A; }  
		else if ((P.x < 6*LARG_BOUTON && P.y > N*TAILLE_CASE) || c=='v') { A.mode = VALIDE; return A; } 
		else if ((850<P.x && P.x<900 && 450<P.y && P.y<500) || P.x==-1) { A.mode = ACTION_CAISSE; return A; } 
		else if ((950<P.x && P.x<1000 && 450<P.y && P.y<500) || P.x==1) { A.mode = ACTION_HOMME; return A; }
		else if ((900<P.x && P.x<950 && 500<P.y && P.y<550) || P.y==1) { A.mode = ACTION_MUR; return A; }
		else if ((900<P.x && P.x<950 && 400<P.y && P.y<450) || P.y==-1) { A.mode = ACTION_OBJECTIF; return A; }
		else if ((P.x < 7*LARG_BOUTON && P.y > N*TAILLE_CASE)) { A.mode = CREA; return A; }
		else {return A;}

	}while(1);

	return A;
}  

