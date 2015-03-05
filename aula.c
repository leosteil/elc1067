#include <stdio.h>

void main (){
	
	FILE* f;
	int matricula;
	char nome [100];
	printf ("Digite a matricula\n");	
	scanf ("%d", &matricula);
	printf ("Digite o nome\n");
	scanf ("%s", nome);
	f = fopen("saida.txt", "w");
	fprintf(f, "%d %s\n", matricula, nome); 
	fclose(f);

}
