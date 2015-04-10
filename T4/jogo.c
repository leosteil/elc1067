/*
 * jogo.c TAD que implementa o jogo de cartas "solitaire".
 * 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014, 2015 João V. Lima, UFSM 2005       Benhur Stein, UFSM
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <assert.h>

#include "jogo.h"
#include "memo.h"
#include "tela.h" 

#define SOLIT_MAGICO 0x50717
#define DESTRUIDO 0x80000000

bool 
jogo_valido(jogo sol)
{
	if (sol == NULL || sol->magico != SOLIT_MAGICO) {
		return false;
	}
	return true;
}

jogo 
jogo_cria(void)
{
	jogo		sol;
	int		i;

	sol = (jogo) memo_aloca(sizeof(jogo_t));
	assert(sol != NULL);
	sol->magico = SOLIT_MAGICO;

	sol->monte = pilha_cria();
	sol->descartes = pilha_cria();
	for (i = 0; i < 4; i++) {
		sol->ases[i] = pilha_cria();
	}
	for (i = 0; i < 7; i++) {
		sol->pilhas[i] = pilha_cria();
	}
	sol->tela = tela_cria();

	return sol;
}

static void 
jogo_destroi_pilha(pilha p)
{
	while (!pilha_vazia(p)) {
		carta_destroi(pilha_remove_carta(p));
	}
	pilha_destroi(p);
}

void 
jogo_destroi(jogo sol)
{
	int		i;
	assert(jogo_valido(sol));
	jogo_destroi_pilha(sol->monte);
	jogo_destroi_pilha(sol->descartes);
	for (i = 0; i < 4; i++) {
		jogo_destroi_pilha(sol->ases[i]);
	}
	for (i = 0; i < 7; i++) {
		jogo_destroi_pilha(sol->pilhas[i]);
	}
	tela_destroi(sol->tela);
	sol->magico |= DESTRUIDO;
	memo_libera(sol);
}

/* acessores */
tela 
jogo_tela(jogo sol)
{
	assert(jogo_valido(sol));
	return sol->tela;
}

pilha 
jogo_monte(jogo sol)
{
	assert(jogo_valido(sol));
	return sol->monte;
}

pilha 
jogo_descartes(jogo sol)
{
	assert(jogo_valido(sol));
	return sol->descartes;
}

pilha 
jogo_ases(jogo sol, int i)
{
	assert(jogo_valido(sol));
	assert(i >= 0 && i < 4);
	return sol->ases[i];
}

pilha 
jogo_pilha(jogo sol, int i)
{
	assert(jogo_valido(sol));
	assert(i >= 0 && i < 7);
	return sol->pilhas[i];
}

void monte_para_descarte(jogo sol){

	carta c = pilha_remove_carta(jogo_monte(sol));
	carta_abre(c);
	pilha_insere_carta(jogo_descartes(sol),c);
	jogo_desenha(sol);
}

void descarte_para_ases(jogo sol){
	
	pilha p  = jogo_ases(sol,1);
	if(pilha_vazia(p)){
		carta c = pilha_remove_carta(jogo_descartes(sol));
		pilha_insere_carta(jogo_ases(sol,0),c);
		jogo_desenha(sol);
	}
}

void descarte_para_jogo(jogo sol){ // move as cartas do descarte para as 7 pilhas
	int ndapilha;
	printw ("\n Digite o numero da pilha pra a qual deseja mover");
	ndapilha = tela_le(sol-> tela);
	ndapilha = ndapilha - 49;
	pilha p = jogo_pilha(sol,ndapilha);
	if(!pilha_vazia(p)){
		carta c = pilha_remove_carta(jogo_descartes(sol));
		pilha_insere_carta(p,c);
		jogo_desenha(sol);
	}
}

void jogo_para_ases(jogo sol, int ndeases){
	pilha p = jogo_ases(sol, ndeases);
	if(pilha_vazia(p)){
		carta c = pilha_remove_carta(jogo_pilha(sol,4));
		pilha_insere_carta(jogo_ases(sol,2),c);
		carta_abre(c); 
		jogo_desenha(sol);
	}
}

void ases_para_jogo(jogo sol, int ndapilha){
	pilha p = jogo_pilha(sol, ndapilha);
	if(!pilha_vazia(p)){
		carta c = pilha_remove_carta(jogo_ases(sol,0));
		pilha_insere_carta(jogo_pilha(sol,0),c);
		jogo_desenha(sol);
	}
}

void jogo_para_jogo(jogo sol){
	int ndapilha,pilhadestino;
	printw ("\nDigite qual pilha deseja mover");
	ndapilha = tela_le(sol->tela);
	printw ("\nDigite para qual pilha deseja mover");
	pilhadestino = tela_le(sol->tela);
	if(!pilha_vazia(p)){
		carta c = pilha_remove_carta(jogo_pilha(sol,ndapilha));
		pilha_insere_carta(jogo_pilha(sol,pilhadestino),c);
		jogo_desenha(sol);
	}
}

