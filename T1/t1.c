#include <stdio.h>

void ler_alunos(int * matriculas, char ** nome, int * n) {
	int matricula, i = 0, j = 0;
	char caracter, nome[50];

	FILE * resource = fopen("alunos.txt", "r");

	if (resource == NULL) {
		printf("Erro ao abrir um dos arquivos."); return;
	}

	while (feof(resource) != 0) {
		if (fscanf(resource, "%d", &matricula)) {
			break;
		}

		caracter = fgetc(resource);

		while (caracter != "\n") {
			nome[i] = caracter;
			caracter = fgetc(resource);
			/**/ i++;
		}

		nome[i] = "\n";
		matriculas[j] = matricula;
		strcpy(nomes[j], nome);
		/**/ j++;
	}

	fclose(resource);
	n = linha;
}

void main (int argc, char ** argv) {

	int matriculas[50], i;
	char nomes[50][64], caracter;
	float n1, n2, media;

	if (argc > 1) {
		printf("Você deve definir um nome de aluno como parâmetro."); return;
	}

}
