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
#include "carta.h" 

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

void abre_carta(jogo sol, pilha p){ // ainda nao utilizada, vai economizar codigo nas funçoes abaixo
	if(!pilha_vazia(p)){
		carta c = pilha_remove_carta(p);
		carta_abre(c);
		pilha_insere_carta(p,c);
	}
	jogo_desenha(sol);
}

void finaliza_jogo(jogo sol){
	printw("\nJogo Finalizado Pelo Usuario\n");
	tela_le(sol->tela);
	jogo_destroi(sol);
	memo_relatorio();
	exit(0);
}

//nao vai ser utilizada porque nao consigo deixar a mesma genetica, pra qualquer movimento
/*void verifica_cor(jogo sol,carta a,carta b,int destino,pilha c, pilha d){
	int verifica = carta_naipe(a) + carta_naipe(b);//se a soma for entre 2 e 4 contando os mesmos, indica diferença
	if (verifica >=2 && verifica<=4){
		pilha_insere_carta(c,b);
		pilha_insere_carta(c,a);
		jogo_desenha(sol);
	}else{
			printw("\nJogada Invalida");
			pilha_insere_carta(c,b);
			pilha_insere_carta(d,a);			
		}
}*/

void monte_para_descarte(jogo sol){ // pronta
	carta c = pilha_remove_carta(jogo_monte(sol));
	carta_abre(c);
	pilha_insere_carta(jogo_descartes(sol),c);
	jogo_desenha(sol);
}

void descarte_para_monte(jogo sol){ //pronta
    while(!pilha_vazia(jogo_descartes(sol))){
	carta c = pilha_remove_carta(jogo_descartes(sol));
	carta_fecha(c);
	pilha_insere_carta(jogo_monte(sol), c);
	jogo_desenha(sol);  
	}
}	

void descarte_para_ases(jogo sol){
	int npdestino;
	printw("\nDigite a pilha de destino de AS");
	npdestino = tela_le(sol->tela);
	npdestino= npdestino-49;
		if(npdestino != 0 && npdestino != 1 && npdestino != 2 && npdestino != 3){
		printw("\nJogada Invalida");
		printw("\nDigite uma pilha de 1 a 4");
		npdestino = tela_le(sol->tela);
		npdestino= npdestino-49;
		if(npdestino != 0 && npdestino != 1 && npdestino != 2 && npdestino != 3){
			printw("\nJogada Invalida\n");
			return;
		}
	}
		
	pilha p = jogo_ases(sol,npdestino);
	carta c = pilha_remove_carta(jogo_descartes(sol));

	if(pilha_vazia(p)){
		if(carta_valor(c) == 1){
			pilha_insere_carta(jogo_ases(sol,npdestino),c);
			jogo_desenha(sol);
			return;
		}else{
			printw ("\nJogada Invalida");
		}
	}
				
	if(!pilha_vazia(p)){
		carta as = pilha_remove_carta(jogo_ases(sol,npdestino)); // carta que esta no monte de as
		if (carta_valor(c) == carta_valor(as)+1 && carta_naipe(c) == carta_naipe(as)){
			pilha_insere_carta(jogo_ases(sol,npdestino),as);
			pilha_insere_carta(jogo_ases(sol,npdestino),c);
			jogo_desenha(sol);
		}else{
			printw("\nJogada invalida");
			pilha_insere_carta(jogo_ases(sol,npdestino),as);
			pilha_insere_carta(jogo_descartes(sol),c);
		}
	}	
}

void descarte_para_jogo(jogo sol){ // move as cartas do descarte para as 7 pilhas
	int npdestino;
	printw ("\n Digite o numero da pilha pra a qual deseja mover");
	npdestino = tela_le(sol-> tela);
	npdestino = npdestino - 49;
	
	if(npdestino != 0 && npdestino != 1 && npdestino != 2 && npdestino != 3 && npdestino != 4 && npdestino != 5 && npdestino !=6 && npdestino != 7 ){
		printw("\nJogada Invalida");
		printw("\nDigite uma pilha de 1 a 7");
		npdestino = tela_le(sol->tela);
		npdestino= npdestino-49;
	}

	pilha p = jogo_pilha(sol,npdestino);
	carta c = pilha_remove_carta(jogo_descartes(sol));

	if(pilha_vazia(p)){
		if(carta_valor(c) == 13){ //se for rei insere na pilha vazia
			pilha_insere_carta(jogo_pilha(sol,npdestino),c);
			jogo_desenha(sol);
			return;
		}else{
			printw("\nJogada Invalida");
		}
	}

	if(!pilha_vazia(p)){
		carta jogo = pilha_remove_carta(jogo_pilha(sol,npdestino)); // carta que esta em uma das 7 pilhas
		if(carta_valor(c) == carta_valor(jogo)-1 && carta_naipe(c) != carta_naipe(jogo)){	
			int verifica = carta_naipe(c) + carta_naipe(jogo);//se a soma for entre 2 e 4 contando os mesmos, indica diferença
			if (verifica >=2 && verifica<=4){
				pilha_insere_carta(jogo_pilha(sol,npdestino),jogo);
				pilha_insere_carta(jogo_pilha(sol,npdestino),c);
				jogo_desenha(sol);
			}else{
				printw("\nJogada Invalida");
				pilha_insere_carta(jogo_pilha(sol,npdestino),jogo);
				pilha_insere_carta(jogo_descartes(sol),c);
				jogo_desenha(sol);			
		}
	}else{
		printw("\nJogada Invalida");
		pilha_insere_carta(jogo_pilha(sol,npdestino),jogo);
		pilha_insere_carta(jogo_descartes(sol),c);
		jogo_desenha(sol);	
	}
	}
}	

void jogo_para_ases(jogo sol){
	int psaida,npdestino;
	printw("\nDigite a pilha de saida");
	psaida = tela_le(sol->tela);
	psaida = psaida -49;

	if(psaida != 0 && psaida != 1 && psaida != 2 && psaida != 3 && psaida != 4 && psaida != 5 && psaida !=6){
		printw("\nJogada Invalida");
		printw("\nDigite uma pilha de 1 a 7");
		psaida = tela_le(sol->tela);
		psaida= psaida-49;
		if(psaida != 0 && psaida != 1 && psaida != 2 && psaida != 3 && psaida != 4 && psaida != 5 && psaida !=6 && psaida != 7){
			printw("\nJogada Invaida");
			return;
		}
	}	

	printw("\nDigite a pilha de AS onde quer inserir a carta");
	npdestino = tela_le(sol->tela);
	npdestino = npdestino -49;

	if(npdestino != 0 && npdestino != 1 && npdestino != 2 && npdestino != 3){
		printw("\nJogada Invalida");
		printw("\nDigite uma pilha de 1 a 4");
		npdestino = tela_le(sol->tela);
		npdestino= npdestino-49;
		if(npdestino != 0 && npdestino != 1 && npdestino != 2 && npdestino != 3){
			printw("\nJogada Invalida\n");
			return;
		}

	}

	pilha p = jogo_ases(sol,npdestino);
	carta c = pilha_remove_carta(jogo_pilha(sol,psaida));
	if(pilha_vazia(p)){
		if(carta_valor(c) == 1){
			pilha_insere_carta(jogo_ases(sol,npdestino),c);
			jogo_desenha(sol);
			abre_carta(sol,jogo_pilha(sol,psaida));
			return;
		}else{
			printw("\nJogada invalida");
		}	
	}

	if(!pilha_vazia(p)){
		carta p_as = pilha_remove_carta(jogo_ases(sol,npdestino));
		if(carta_valor(c) == carta_valor(p_as)+1 && carta_naipe(c) == carta_naipe(p_as)){
			pilha_insere_carta(jogo_ases(sol,npdestino),p_as);
			pilha_insere_carta(jogo_ases(sol,npdestino),c);
			jogo_desenha(sol);
			abre_carta(sol,jogo_pilha(sol,psaida));	
		}else{
			printw("\nJogada invalida");
			pilha_insere_carta(jogo_ases(sol,npdestino),p_as);
			pilha_insere_carta(jogo_pilha(sol,psaida),c);
		}
	}	
}

void ases_para_jogo(jogo sol){
	int psaida,npdestino;
	printw("\nDigite a pilha de saida");
	psaida = tela_le(sol->tela);
	psaida = psaida -49;

	if(psaida != 0 && psaida != 1 && psaida != 2 && psaida != 3){
		printw("\nJogada Invalida");
		printw("\nDigite uma pilha de 1 a 4");
		psaida = tela_le(sol->tela);
		psaida= psaida-49;
		if(psaida != 0 && psaida != 1 && psaida != 2 && psaida != 3 && psaida != 4 && psaida != 5 && psaida !=6 && psaida != 7){
			printw("\nJogada Invaida");
			return;
		}
	}	

	printw("\nDigite a pilha onde quer inserir a carta");
	npdestino = tela_le(sol->tela);
	npdestino = npdestino -49;

	if(npdestino != 0 && npdestino != 1 && npdestino != 2 && npdestino != 3 && npdestino != 4 && npdestino != 5 && npdestino != 6){
		printw("\nJogada Invalida");
		printw("\nDigite uma pilha de 1 a 7");
		npdestino = tela_le(sol->tela);
		npdestino= npdestino-49;
		if(npdestino != 0 && npdestino != 1 && npdestino != 2 && npdestino != 3 && npdestino != 4 && npdestino != 5 && npdestino != 6){
			printw("\nJogada Invalida\n");
			return;
		}
	}

	pilha p = jogo_pilha(sol,npdestino);
	carta c = pilha_remove_carta(jogo_ases(sol,psaida));

	if(pilha_vazia(p)){
		if(carta_valor(c) == 13){
			pilha_insere_carta(jogo_pilha(sol,npdestino),c);
			jogo_desenha(sol);
			abre_carta(sol,jogo_ases(sol,psaida));
			return;
		}else{
			printw("\nJogada invalida");
		}	
	}

	if(!pilha_vazia(p)){
		carta jogo = pilha_remove_carta(jogo_pilha(sol,npdestino));
		if(carta_valor(c) == carta_valor(jogo)+1 && carta_naipe(c) != carta_naipe(jogo)){
			int verifica = carta_naipe(c) + carta_naipe(jogo);//se a soma for entre 2 e 4 contando os mesmos, indica diferença
			if (verifica >=2 && verifica<=4){
			pilha_insere_carta(jogo_pilha(sol,npdestino),jogo);
			pilha_insere_carta(jogo_pilha(sol,npdestino),c);
			jogo_desenha(sol);
		}else{
			printw("\nJogada invalida");
			pilha_insere_carta(jogo_ases(sol,npdestino),jogo);
			pilha_insere_carta(jogo_pilha(sol,psaida),c);
		}
		}
	}
}	

void jogo_para_jogo(jogo sol){
	int psaida,npdestino;
	printw ("\nDigite qual pilha deseja mover");
	psaida = tela_le(sol->tela);
	psaida = psaida - 49;

	printw ("\nDigite para qual pilha deseja mover");
	npdestino = tela_le(sol->tela);
	npdestino = npdestino -49;

	pilha p = jogo_pilha(sol,npdestino);
	carta c = pilha_remove_carta(jogo_pilha(sol,psaida));

	if(pilha_vazia(p)){
		if(carta_valor(c) == 13){
			pilha_insere_carta(jogo_pilha(sol,npdestino),c);
			jogo_desenha(sol);
			/*if(!pilha_vazia(jogo_pilha(sol,psaida))){
				carta aux = pilha_remove_carta(jogo_pilha(sol,psaida));
				carta_abre(aux);
				pilha_insere_carta(jogo_pilha(sol,psaida),aux);
				jogo_desenha(sol);
			}*/
			abre_carta(sol,jogo_pilha(sol,psaida));
			return;	
		}
	}

	if(!pilha_vazia(p)){
		carta jogo = pilha_remove_carta(jogo_pilha(sol,npdestino)); // carta que esta na pilha destino
		if(carta_valor(c) == carta_valor(jogo)-1 && carta_naipe(c) != carta_naipe(jogo)){
			pilha_insere_carta(jogo_pilha(sol,npdestino),jogo);
			pilha_insere_carta(jogo_pilha(sol,npdestino),c);
			jogo_desenha(sol);
			/*if(!pilha_vazia(jogo_pilha(sol,psaida))){
				carta aux = pilha_remove_carta(jogo_pilha(sol,psaida));
				carta_abre(aux);
				pilha_insere_carta(jogo_pilha(sol,psaida),aux);
				jogo_desenha(sol);
			}*/
			abre_carta(sol,jogo_pilha(sol,psaida));	
		}else{
			printw("\nJogada invalida");
			pilha_insere_carta(jogo_pilha(sol,npdestino),jogo);
			pilha_insere_carta(jogo_pilha(sol,psaida),c);
		}
	}	
	
}

