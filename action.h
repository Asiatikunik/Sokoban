// action.h du projet SOKOBAN
// Dang Thanh Duy 21607229  AKA BlackyStaar

#ifndef ___ACTIONS_H
#define ___ACTIONS_H

/*struct mode{ 
	TABLEAU tableau;
	ACTION action;
}
typedef struct mode MODE;
*/

struct action {
	int mode;
	int x,y;
};
typedef struct action ACTION;

ACTION recuperer_action();
int mode_action(ACTION A);

void test_arrow();


#endif
