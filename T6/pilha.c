#include <sdtio.h>
#include <stdlib.h>
#include "pilha.h"

/* retorna uma nova pilha, vazia */
pilha_t *pilha_cria(void){
        pilha_t* p = (pilha_t*) memo_aloca(sizeof(pilha_t));
        p->prim = NULL;
        return p;
}

/* destroi a pilha */
void pilha_destroi(pilha_t* p){
        lista_t* q = p->prim;
        while (q!=NULL){
                lista_t* t = q->prox;
                //printf ("\nLiberando %.2f\n", q->info);
                memo_libera(q);
                q = t;
        }
        memo_libera(p);
}

/* retorna true se a pilha p estiver vazia. */
bool pilha_vazia(pilha_t* p){
        lista_t* q = p->prim;
        if (q == NULL){
                return true;
        }else{
                return false;
        }
}

/* insere o dado arv do tipo arv_t na pilha p */
void pilha_insere(pilha_t* p, arv_t* arv){
	lista_t* q = (Lista*) malloc(sizeof(Lista));
	n->info = arv;
	n->prox = p->prim;
	p->prim = n;
}

/* remove e retorna o nó operador/operando no topo da pilha */
arv_t* pilha_remove(pilha_t p){
	lista_t* q;
	arv_t* arv
	if (pilha_vazia(p)){
		printf("Pilha vazia.\n");
		/* aborta programa */
		exit(1);
	}
	t = p->prim;
	v = t->info;
	p->prim = t->prox;
	memo_libera(t);
	return arv;
}

/* retorna true se p for uma pilha válida */
bool pilha_valida(pilha_t p){
	
}

