// action.h du projet SOKOBAN
// Dang Thanh Duy   AKA BlackyStaar

#include <stdio.h>
#include <stdlib.h>
#include "action.h"
#include <uvsqgraphics.h>
#include "constantes.h"

ACTION recuperer_action() {
	ACTION A;
	POINT P = wait_clic();
	if (P.y < N*TAILLE_CASE) {
		A.mode = GRILLE;
		A.x = P.x/TAILLE_CASE;
		A.y = P.y/TAILLE_CASE;
		return A;
	}
	if (P.x <   LARG_BOUTON) { A.mode = JOUER;     return A; }
	if (P.x < 2*LARG_BOUTON) { A.mode = SELECT; return A; }
	if (P.x < 3*LARG_BOUTON) { A.mode = PREC; return A; }
	if (P.x < 4*LARG_BOUTON) { A.mode = SUIV;   return A; }
	if (P.x < 5*LARG_BOUTON) { A.mode = QUITTER;   return A; } 

	return A;
}

int mode_action(ACTION A) {
	return A.mode;
}