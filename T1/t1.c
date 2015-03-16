#include <stdio.h>
#include <string.h>

void ler_alunos(int * matriculas, char nomes[][50], int * n) {
	int matricula, i = 0, j = 0;
	char caracter, nome[50];

	FILE *arq;
	arq = fopen("alunos.txt", "r");

	if (arq == NULL) {
		printf("Erro ao abrir um dos arquivos."); return;
	}

	while (feof(arq) == 0) {
		if (fscanf(arq, "%d", &matricula)<=0) {
			break;
		}

		caracter = fgetc(arq);

		while (caracter != '\n') {
			nome[i] = caracter;
			caracter = fgetc(arq);
			/**/ i++;
		}

		nome[i] = '\0';
		matriculas[j] = matricula;
		strcpy(nomes[j], nome);
		/**/ j++;
	}

	fclose(arq);
	*n = j;
}

float media(int * matricula) {
	int media;
	float n1, n2;

	FILE *arq;
	arq = fopen("notas.txt", "r");

	if (arq == NULL) {
		printf("Erro ao abrir um dos arquivos."); return;
	}

	while (feof(arq) != 0) {
		if (fscanf(arq, "%d", &media)) {
			break;
		}

		if (media == *matricula) {
			if (fscanf(arq, "%f %f", &n1, &n2)) {
				return (n1 + n2) / 2;
			}
		}
	}

	return 0.0;
}

void main (int argc, char ** argv) {

	int matriculas[50], matricula, linhas, linha, i;
	char nomes[50][64], nome[64], caracter;

	if (argc > 1) {
		printf("Você deve definir um nome de aluno como parâmetro."); return;
	}

	ler_alunos(matriculas, nomes, linhas);

	for (i = 0; i <= linhas; i++) {
		if (strcmp(nomes[i], nome) >= 0) {
			matricula = matriculas[i];
			nome = nomes[i];
			printf("Aluno %s(%d) tem média: %f", nome, matricula, media(matricula));
		}
	}
}
