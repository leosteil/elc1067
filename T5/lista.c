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

/* implementa aqui sua estrutura lista_t duplamente encadeada */

marc* lista_cria(void){
	lista_t* novo = (lista_t*) memo_aloca(sizeof(lista_t));
	novo->prox = NULL;
	novo->ant  = NULL;
	novo->texto[0] = '\0';

	marc* marcador = (marc*) memo_aloca(sizeof(marc));
	marcador->prim = novo;
	marcador->ultim = novo;

	return marcador;
} 

void lista_destroi(marc* marcador){
	memo_libera(marcador->prim->texto);
	memo_libera(marcador->prim);
	memo_libera(marcador);
}

