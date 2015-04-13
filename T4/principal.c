/*
 * principal.c Esse programa testa as TADs implementadas para um jogo
 * solitário.
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#include "memo.h"
#include "jogo.h"
#include "vetor.h"
#include "jogo.h"
#include "fila.h"
#include "pilha.h" 
#include "tela.h" 



void inicia_jogo(jogo solit){
	vetor_t* cartas = vetor_cria();
	vetor_t* fora_ordem = vetor_cria();
	srand(time(NULL));
	int i,j;
	carta c;
	
	for(i=0; i<4; i++){	// cria as cartas 
		for(j=1; j<=13;j++){
			vetor_insere_carta(cartas, (i*13)+j-1, carta_cria(j,i));
		}
	}

	for (i=0; i<52;i++){ // embaralhamento das cartas
		do{
			j=((int) rand()) % vetor_numelem(cartas);
			c = vetor_remove_carta(cartas,j);
		}while(c == NULL);
		vetor_insere_carta(fora_ordem, i, c);
	}	
	
	for(i=0; i<7; i++){ // pilhas
		
		for(j=0;j<=i; j++){ // cartas
			c = vetor_remove_carta(fora_ordem,0);
			pilha_insere_carta(jogo_pilha(solit,i),c);		
		}
		carta_abre(c); // esta no topo
	}
	
	for(i=0; i<52-28; i++){
		carta c = vetor_remove_carta(fora_ordem,0);
		pilha_insere_carta(jogo_monte(solit),c);	
	}
}

int 
main(int argc, char **argv)
{
	jogo		solit;
	solit = jogo_cria();
	inicia_jogo(solit);

	jogo_desenha(solit);
	while (!pilha_vazia(jogo_monte(solit))) {
		char tecla = tela_le(jogo_tela(solit));
		//comandos_tela(solit->tela);
		switch(tecla){
			case ' ':
				monte_para_descarte(solit);
				if(pilha_vazia(jogo_monte(solit))){
					descarte_para_monte(solit);
				}
				break;
			case 'g':
				descarte_para_ases(solit);
				break;
			case 'h':
				descarte_para_jogo(solit);
				break;
			case 'j':
				jogo_para_ases(solit);
				break;
			case 'k':
				ases_para_jogo(solit,0);
				break;
			case 'l':
				jogo_para_jogo(solit);
				break;
		}
	}
	tela_le(jogo_tela(solit));
	jogo_destroi(solit);

	/* relatório de memória */
	memo_relatorio();
	return 0;
}
