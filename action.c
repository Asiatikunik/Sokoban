// action.h du projet SOKOBAN
// Dang Thanh Duy   AKA BlackyStaar

#include <stdio.h>
#include <stdlib.h>
#include <uvsqgraphics.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "action.h"
#include "constantes.h"
#include "jeu.h"

ACTION recuperer_action() {
	ACTION A;
	POINT P = wait_clic();

	if (P.x < 1*LARG_BOUTON && P.y > N*TAILLE_CASE) { A.mode = QUIT; return A; }
	else if (P.x < 2*LARG_BOUTON && P.y > N*TAILLE_CASE) { A.mode = UNDO; return A; }
	else if (P.x < 3*LARG_BOUTON && P.y > N*TAILLE_CASE) { A.mode = REDO; return A; }
	else if (P.x < 4*LARG_BOUTON && P.y > N*TAILLE_CASE) { A.mode = INIT; return A; }
	else if (P.x < 5*LARG_BOUTON && P.y > N*TAILLE_CASE) { A.mode = PRED; return A; } 
	else if (P.x < 6*LARG_BOUTON && P.y > N*TAILLE_CASE) { A.mode = SUIV; return A; } 
	else if (850<P.x && P.x<900 && 450<P.y && P.y<500) { A.mode = GAUCHE; return A; } 
	else if (950<P.x && P.x<1000 && 450<P.y && P.y<500) { A.mode = DROITE; return A; }
	else if (900<P.x && P.x<950 && 500<P.y && P.y<550) { A.mode = HAUT; return A; }
	else if (900<P.x && P.x<950 && 400<P.y && P.y<450) { A.mode = BAS; return A; }
	else {A.mode = RIEN; return A;}

/*
	haut1.x=900; haut1.y=550;
    haut2.x=950; haut2.y=500;
    bas1.x=900; bas1.y=450;
    bas2.x=950; bas2.y=400;
*/
	return A;
}

int mode_action(ACTION A) {
	return A.mode;
}


/*
int kbhit(void) {
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF){
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

int read_keybord() {
	int key;
	if (kbhit())
		key = getc(stdin);
	else
		key = 0;
	return key;
}

*/