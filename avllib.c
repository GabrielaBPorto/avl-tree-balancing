#include "avllib.h"
#include <stdio.h>
#include <stdlib.h>

void desalocar(no_t **no){
	if((*no) == NULL)
		return;
	desalocar(&(*no)->left);
	desalocar(&(*no)->right);

	free((*no));
}

void insere(no_t **root,int valor){
	no_t *is;
	is = insere_no(&(*root),valor);
	printf("i %d\n", valor);
	atualiza_altura(&(*root));
	is = busca_no(*root, valor, 0);
	fator_balanceamento(&(*root), is);
	imprime_arvore(*root);
	printf("\n");
}

void remocao(no_t **root, int valor, int controle){
	int isi;
	isi = remove_no(&(*root), valor, controle);
	if(isi){
		printf("r %d\n",valor);
		imprime_arvore(*root);
		printf("\n");
	}
	else{
		printf("O valor %d não está na árvore para ser removido \n", valor);
	}
}

void buscar(no_t *root, int valor, int controle){
	no_t *is;
	printf("b %d\n",valor );
	is = busca_no(root, valor, controle);
	printf("\n");
	if(!is)
		printf("O valor %d não está na árvore \n", valor);
}

//Cria o nó
no_t *CriaNo(int valor){
	no_t *temp;
	temp = (no_t *) malloc (sizeof(no_t));
	temp->key = valor;
	temp->right = temp->left = NULL;
	temp->pai = NULL;
	//é inserido como nó folha
	temp->hesq = 0;
	temp->hdir = 0;
	return(temp);
}

int ehraiz(no_t *no){
	if(no->pai == NULL){
		return(1);
	}
	else{
		return(0);
	}
}

no_t *insere_no(no_t **no, int valor){
	if((*no) == NULL){
		*no = CriaNo(valor);
		return(*no);
	}
	else{
		if(valor < (*no)->key){
			/*Ajeita o no->pai */
			no_t *leftchild = insere_no(&(*no)->left, valor);
			(*no)->left = leftchild;
			leftchild->pai = *no;
		}
		else{
			/*Ajeita o no->pai */
			no_t *rightchild = insere_no(&(*no)->right, valor);
			(*no)->right = rightchild;
			rightchild->pai = *no;
		}
	}
	return(*no);
}

//Realiza o transplante de nó u por v
void Transplant(no_t **root, no_t *u, no_t *v){
	if(u == NULL){
		return;
	}
	if(u->pai == NULL){
		(*root) = v;
	}
	else if(u == u->pai->left)
		u->pai->left = v;
	else
		u->pai->right = v;
	if(v != NULL)
		v->pai = u->pai;
	return;
}

//Imprime a árvore de maneira pre-order
void imprime_arvore(no_t *no){
	if (no != NULL){
		/*Quando o nó começa assume que ele está dentro de uma árvore e imprime*/
		printf("(%d,", no->key);
		imprime_arvore(no->left);
		/*Entre uma árvore e outra existe diferença */
		imprime_arvore(no->right);
		printf(")");
		return;
	}
	/*Se o nó estiver vazio imprime nó vazio e volta */
	printf("()");
	return;
}

// Entrada de controle para saber se é para imprimir os nodos ou nao
no_t* busca_no(no_t *no, int valor, int controle){
	if(no == NULL){
		return(NULL);
	}
	if(no->key == valor){
		return(no);
	}
	if(controle){
		printf("%d ",no->key);
	}
	if(no->key > valor){
		return(busca_no(no->left, valor, controle));
	}
	else{
		return(busca_no(no->right, valor, controle));
	}
}

//Procura o proximo nó que tem o valor próximo a nó
no_t *proximo(no_t *no){
	if(no->left == NULL)
		return(no);
	else
		return(proximo(no->left));
}

//Procura o nó anterior que tem o valor próximo a nó
no_t *antecessor(no_t *no){
	if(no->right == NULL){
		return(no);
	}
	return(antecessor(no->right));
}

//Procura o nó a ser removido, faz o transplante e remove
int remove_no(no_t **root, int valor, int controle){
	no_t *no;
	no = busca_no(*root,valor,controle);
	if(no == NULL){
		return(0);
		//O nó nao existe
	}
	if(no->left == NULL){
		Transplant(&(*root),no,no->right);
	}
	else if(no->right == NULL){
		Transplant(&(*root),no,no->left);
	}
	else {
		no_t *new = antecessor(no->left);
		if(!new){
			new = proximo(no->right);
			if(new->pai != no){
				Transplant(&(*root),new,new->right);
				new->left = no->right;
				new->left->pai = new;
			}
			Transplant(&(*root),no,new);
			new->left = no->left;
			new->left->pai = new;
		}
		else{
			if(new->pai != no){
				Transplant(&(*root),new,new->left);
				new->left = no->left;
				new->left->pai = new;
			}
			Transplant(&(*root),no,new);
			new->right = no->right;
			new->right->pai = new;
			}
		}
	no_t *temp = no->pai;
	atualiza_altura(&(*root));
	fator_balanceamento(&(*root), temp);
	return(1);
}

int max(int a, int b){
	if(a > b){
		return(a);
	}
	else{
		return(b);
	}
}

void fator_balanceamento(no_t **root, no_t *no){
	if(no == NULL){
		return;
	}
	no_t *temp = NULL;
	if(no->hesq - no->hdir < -1){
		temp = no->right;
		if(temp->hesq > temp->hdir){
			rotaciona_direita(&(*root),&temp);
		}
		atualiza_altura(&no);
		rotaciona_esquerda(&(*root),&no);
		atualiza_altura(&no);
	}
	if(no->hesq - no->hdir > 1){
		temp = no->left;
		if(temp->hesq < temp->hdir){
			rotaciona_esquerda(&(*root),&temp);
		}
		atualiza_altura(&no);
		rotaciona_direita(&(*root),&no);
		atualiza_altura(&no);
	}
	atualiza_altura(&no);
	fator_balanceamento(&(*root),no->pai);
	return;
}

int atualiza_altura(no_t **no){
	if((*no)==  NULL)
		return(0);
	(*no)->hesq = atualiza_altura(&(*no)->left);
	(*no)->hdir = atualiza_altura(&(*no)->right);
	//Isso quer dizer que encontrou um pai com um filho só, se o lado esquerdo for null, soma na altura dele, e devolve a altura da direita
	if((*no)->hesq == 0)
		return((*no)->hdir+1);
	if((*no)->hdir == 0)
		return((*no)->hesq+1);
	return(max((*no)->hesq,(*no)->hdir) + 1);
}

void rotaciona_esquerda(no_t **root, no_t **no){
	no_t *y = (*no)->right;
	(*no)->right = y->left;
	if(y->left != NULL)
		y->left->pai = (*no);
	y->pai = (*no)->pai;
	if((*no)->pai == NULL)
		(*root) = y;
	else if((*no) == (*no)->pai->left)
		(*no)->pai->left = y;
	else
		(*no)->pai->right = y;
	y->left = (*no);
	(*no)->pai = y;
	return;
}

void rotaciona_direita(no_t **root, no_t **no){
	no_t *y = (*no)->left;
	(*no)->left = y->right;
	if(y->right != NULL)
		y->right->pai = (*no);
	y->pai = (*no)->pai;
	if((*no)->pai == NULL)
		(*root) = y;
	else if((*no) == (*no)->pai->right)
		(*no)->pai->right = y;
	else
		(*no)->pai->left = y;
	y->right = (*no);
	(*no)->pai = y;
	return;
}