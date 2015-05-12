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
#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdlib.h>
#include "memo.h"


//cada no dessa lista e uma linha do editor
struct lista{
	char* texto;
	struct lista* prox;
	struct lista* ant;
};
typedef struct lista lista_t;

struct marcador{
	lista_t* prim;
	lista_t* ultm;
	
};
typedef struct marcador marc;


//cria uma lista
marc* lista_cria(void);

//destoi uma lista
void lista_destroi(marc* marcador);

//insere elementos na lista
marc* lista_insere(marc* marcador, int pos);

//remove elementos na lista
marc* lista_remove(marc* marcador, int pos);

//busca elementos da lista
lista_t* lista_busca(marc* marcador, int pos);

//imprime a lista 
void lista_imprime (lista_t* l);

//retorna o ultimo elemento da lista
lista_t* ultimo(lista_t* l);

#endif /* _LISTA_H_ */
