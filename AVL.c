#include "avllib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	no_t *root = NULL;
	FILE *entrada;
	char c;
	int valor;

	if(argc >=2){
		entrada = fopen(argv[1],"r");
	}
	else{
		entrada = stdin;
	}

	while(fscanf(entrada,"%c", &c) == 1){
		fscanf(entrada,"%d", &valor);
		if(c == 'i'){
			insere(&root,valor);
		}
		if(c == 'b'){
			buscar(root,valor,1);
		}
		if(c == 'r'){
			remocao(&root, valor, 0);
		}
	}
	fclose(entrada);
	desalocar(&root);
	return 0;
}