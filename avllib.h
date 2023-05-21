#ifndef __AVLLIB__
#define __AVLLIB__

typedef struct no_t{
	int key;
	struct no_t *right;
	struct no_t *left;
	struct no_t *pai;
	int hdir;
	int hesq;
} no_t;

void desalocar(no_t **root);

void insere(no_t **root,int valor);

void remocao(no_t **root, int valor, int controle);

void buscar(no_t *root, int valor, int controle);

int max(int a, int b);

no_t *CriaNo(int key);

no_t *insere_no(no_t **no, int valor);

void imprime_arvore(no_t *no);

no_t *busca_no(no_t *no, int valor, int controle);

int remove_no(no_t **root, int valor, int controle);

no_t *antecessor(no_t *no);

no_t *proximo(no_t *no);

void Transplant(no_t **root, no_t *a, no_t *b);

int atualiza_altura(no_t **no);

void fator_balanceamento(no_t **root, no_t *no);

void rotaciona_direita(no_t **root, no_t **no);

void rotaciona_esquerda(no_t **root, no_t **no);

#endif