all: busca

busca: AVL.c avllib.o
	gcc AVL.c avllib.o -Wall -g -o busca

avllib.o: avllib.c avllib.h
	gcc avllib.c -c
clean: 
	-rm *.o
purge:
	-rm busca
