// constantes.h du projet SOKOBAN
// Dang Thanh Duy 21607229  AKA BlackyStaar

#ifndef __CONSTANTES_H
#define __CONSTANTES_H

#define TAILLE_TAB 50
#define TAILLE_CASE_JEU 25

#define QUIT   0
#define UNDO   1
#define REDO   2
#define INIT   3
#define PRED   4
#define SUIV   5
#define GAUCHE 6
#define DROITE 7
#define HAUT   8
#define BAS    9
#define RIEN   10

#define MUR 1
#define CAISSE 2
#define OBJECTIF 3
#define HOMME 4
#define VIDE 5
#define HOMME_OBJECTIF 6
#define CAISSE_OBJECTIF 7

#define LARGEUR_AFFICHAGE 1005
#define HAUTEUR_AFFICHAGE 650
#define TAILLE_CASE 43
#define LARG_BOUTON ((N*TAILLE_CASE)/5.6)
#define HAUT_BOUTON (TAILLE_CASE)
#define LARG_FENETRE (N*TAILLE_CASE)
#define HAUT_FENETRE (N*TAILLE_CASE + HAUT_BOUTON)
#define TAILLE_POLICE 20

//surement a effacer
#define N 14

//A changer les valeurs
//#define COUL_FOND antiquewhite
#define COUL_FOND argent
#define COUL_BORD bleu
#define COUL_CROIX jaune
#define COUL_BOUTON lightskyblue

#endif