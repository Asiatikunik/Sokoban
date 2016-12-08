#Makefile du projet Sokoban

all: main
	./main

main: main.o affiche.o action.o
	gcc -o main main.o affiche.o action.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

main.o: main.c affiche.h
	gcc -c -g -Wall main.c

affiche.o: affiche.c affiche.h
	gcc -c -g -Wall `sdl-config --cflags` affiche.c
	

clean:
	rm -f affiche.o
	rm -f main.o
	rm -f main
