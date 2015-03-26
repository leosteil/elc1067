#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ler_alunos(int *matriculasAluno, char **nomes, int *n) {
	int matricula, i = 0, j = 0;
	char caracter, nome[50];

	FILE *arq;
	arq = fopen("alunos.txt", "r");

	if (arq == NULL) { // impede que seja lido, caso nao tenha nada no arquivo
		printf("Erro ao abrir um dos arquivos."); return;
	}

	while (feof(arq) == 0) { //funçao feof indica o final de um arquivo , retorna 0 se nao chegou ao fim
		if (fscanf(arq, "%d", &matricula)<=0) {
			break;
		}

		caracter = fgetc(arq); // copia para a variavel do tipo char caracter o primeiro caracter da primeira linha do arquivo
		i=0;

		while (caracter != '\n' && feof(arq) == 0) { //enquanto nao passar de linha, no caso \n, ele continua copiando a primeira linha no nome[i]
			nome[i] = caracter; // passa o caracter ja existente 
			caracter = fgetc(arq); //vai copiando os restantes do caracter da coluna
			/**/ i++;
		}

		//ate aqui esta certo
		//erro desta parte resolvido

		nome[i] = '\0'; // acrescenta um \0 ao final da string lida acima
		matriculasAluno[j] = matricula; // coloca a matricula salva no primeiro while para matriculas[j]
		nomes[j]= (char*) malloc ((strlen(nome)+1)* sizeof(char));
		strcpy(nomes[j], nome); //copia o nome para o vetor que armazena a string //ERRO AQUI !!!!!!!!!!!!!!!!!!!!
		/**/ j++;
	}

	fclose(arq);
	*n = j;
}

void ler_notas_e_media(int * matriculasNotas,float *notas) { // erro na funçao medias encontrado, passa float mais tinha na versao anterior int como parametro
	int i = 0, matricula;
	float n1=0, n2=0;

	FILE *arq;
	arq = fopen("notas.txt", "r");

	if (arq == NULL) {
		printf("Erro ao abrir um dos arquivos."); return;
	}

	while (feof(arq) == 0) { // copia as notas do  arquivo para n1 e n2
		if (fscanf(arq, " %d %f %f ",&matricula, &n1, &n2)<=0) {
			break;
		}

		matriculasNotas[i] = matricula;
		notas[i] = (n1+n2)/2;
		i++;
	}

	fclose(arq);
}

void verifica_matricula_e_printa(int *matriculasNotas, int *matriculasAluno, char *nome, char **nomes, float *medias, int *linha){
	int i, j;
    for(i = 0; i < *linha; i++){
        j = 0;
        if(strstr(nomes[i], nome) != NULL){
            while(matriculasAluno[i] != matriculasNotas[j] && matriculasNotas[j]>0)
                j++;
            printf("%.2f %s\n", medias[j], nomes[i]);
        }
    }
}

void main (int argc, char ** argv) {

	int *matAlunos, *matNotas,linha =0 , i, n;
	char **nomes, *nome;
	float *medias;

	matAlunos = (int*) malloc(50*sizeof(int));
	matNotas = (int*) malloc(50*sizeof(int));
	nomes = (char**) malloc(50*sizeof(char*));
	nome = (char*) malloc (50*sizeof(char));
	medias = (float*) malloc (50*sizeof(float));

	if (argc > 1) {
		strcpy(nome , argv[1]);
	}

	ler_alunos(matAlunos, nomes, &linha);
	ler_notas_e_media(matNotas, medias);
	verifica_matricula_e_printa(matNotas, matAlunos, nome, nomes, medias, &linha);

	/*for (i = 0; i < linha; i++) {
		if (strstr(nomes[i], nome) != NULL) {
			printf("%s %.3f\n", nomes[i], medias[i]);
		}
	}*/

	free (matAlunos);
	free (matNotas);
	
	for(i=0; i<n; i++)
		free(nomes[i]);

	free (nome);
	free (medias);
};

