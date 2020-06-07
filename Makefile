
build: main.c file.c file.h
	gcc -o fsminishell main.c file.c -g -Wall

run: fsminishell
	./fsminishell

.PHONY : CLEAN
CLEAN:
	rm -f fsminishell
	rm -f *.out