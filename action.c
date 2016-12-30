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
	if (P.y < N*TAILLE_CASE) {
		A.mode = INIT;
		A.x = P.x/TAILLE_CASE;
		A.y = P.y/TAILLE_CASE;
		return A;
	}
	if (P.x <   LARG_BOUTON) { A.mode = QUIT; return A; }
	if (P.x < 2*LARG_BOUTON) { A.mode = UNDO; return A; }
	if (P.x < 3*LARG_BOUTON) { A.mode = REDO; return A; }
	if (P.x < 4*LARG_BOUTON) { A.mode = INIT; return A; }
	if (P.x < 5*LARG_BOUTON) { A.mode = PRED; return A; } 
	if (P.x < 6*LARG_BOUTON) { A.mode = SUIV; return A; } 


	return A;
}

int mode_action(ACTION A) {
	return A.mode;
}



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

