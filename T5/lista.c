/*
 * lista.h
 * Funções de TAD lista duplamente encadeada.
 *
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014, 2015 João V. F. Lima, UFSM
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "lista.h"
#include "memo.h"
#include <stdio.h>

/* implementa aqui sua estrutura lista_t duplamente encadeada */

marc* lista_cria(void){
	lista_t* novo = (lista_t*) memo_aloca(sizeof(lista_t));
	novo->prox = NULL;
	novo->ant  = NULL;

	novo->texto = (char*) memo_aloca(sizeof(char));
	novo->texto[0] = '\0';

	marc* marcador = (marc*) memo_aloca(sizeof(marc));
	marcador->prim = novo;
	marcador->ultm = novo;

	return marcador;
} 

void lista_destroi(marc* m){
	memo_libera(m->prim->texto);
	memo_libera(m->prim);
	memo_libera(m);
}


marc* lista_insere(marc* marcador, int pos){
	lista_t* novo = (lista_t*) memo_aloca(sizeof(lista_t));
	novo->texto = (char*) memo_aloca(sizeof(char));
	novo->texto[0] = '\0';
	if(pos == 1){
		novo->ant = NULL;
		novo->prox = marcador->prim;
		marcador->prim->ant = novo;
		marcador->prim = novo;
	}else{
		novo->ant = lista_busca(marcador, pos-1);
		novo->prox = lista_busca(marcador, pos-1)->prox;
		if(lista_busca(marcador, pos-1)->prox != NULL){
			lista_busca(marcador, pos-1)->prox->ant = novo;
		}else{
			marcador->ultm = novo;
		}
		lista_busca(marcador, pos-1)->prox = novo;
	}
	return marcador;
}

/*void lista_imprime (lista_t* l){
	lista_t* p;
	for(p=l;p!=NULL;p=p->prox){
		printf("info = %s\n",p->texto);
	}
}*/

lista_t* lista_busca(marc* marcador, int pos){
	int i;
	lista_t* p = marcador->prim;
	for(i = 1; i < pos; i++){
		p = p->prox;
	}
	return p;
}

marc* lista_remove(marc* marcador, int pos){
	lista_t* p = lista_busca(marcador, pos);
	if(p->prox != NULL){
		p->prox->ant = p->ant;
	}else{
		marcador->ultm = p->ant;
	}
	if(p->ant != NULL){
		p->ant->prox = p->prox;
	}else{
		marcador->prim = p->prox;
	}
	memo_libera(p->texto);
	memo_libera(p);
	return marcador;
}