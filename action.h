// action.h du projet SOKOBAN
// Dang Thanh Duy   AKA BlackyStaar


#ifndef ___ACTIONS_H
#define ___ACTIONS_H

struct action {
	int mode;
	int x,y;
};

typedef struct action ACTION;

ACTION recuperer_action();
int mode_action(ACTION A);

#endif
