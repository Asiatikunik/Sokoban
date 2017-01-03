# Makefile du projet Sokoban
# Dang Thanh Duy 21607229  AKA BlackyStaar

all: $(sokoban)
		./sokoban

sokoban: sokoban.o affiche.o action.o jeu.o
	gcc -o sokoban sokoban.o affiche.o action.o jeu.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

sokoban.o: sokoban.c affiche.h constantes.h
	gcc -c -g -Wall sokoban.c

affiche.o: affiche.c affiche.h sokoban.h constantes.h
	gcc -c -g -Wall `sdl-config --cflags` affiche.c
	
action.o: action.c action.h constantes.h
	gcc -c -g -Wall `sdl-config --cflags` action.c

jeu.o: jeu.c jeu.h constantes.h
	gcc -c -g -Wall `sdl-config --cflags` jeu.c

clean:
	rm -f affiche.o
	rm -f sokoban.o
	rm -f sokoban
	rm -f action.o
	rm -f jeu.o

