# Makefile du projet Sokoban
# Thanh Duy Dang  AKA BlackyStaar

all: main
		./main

main: main.o affiche.o action.o jeu.o
	gcc -o main main.o affiche.o action.o jeu.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

main.o: main.c affiche.h constantes.h
	gcc -c -g -Wall main.c

affiche.o: affiche.c affiche.h main.h constantes.h
	gcc -c -g -Wall `sdl-config --cflags` affiche.c
	
action.o: action.c action.h constantes.h
	gcc -c -g -Wall `sdl-config --cflags` action.c

jeu.o: jeu.c jeu.h constantes.h
	gcc -c -g -Wall `sdl-config --cflags` jeu.c

clean:
	rm -f affiche.o
	rm -f main.o
	rm -f main
	rm -f action.o
	rm -f jeu.o