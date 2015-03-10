#include <stdio.h>

void main (){
	
	FILE* f;
	/*int matricula;
	char nome [100];
	printf ("Digite a matricula\n");	
	scanf ("%d", &matricula);
	printf ("Digite o nome\n");
	scanf ("%s", nome);*/
	char c[100];
	f = fopen("saida.txt", "r");

	while(fgets(c, 100, f) != NULL){ /*foi a unica forma que consegui fazer, nao consegui fazer usando o fscanf*/
		printf ("%s", c);
	}

	//fscanf(f,"%s\n",c); 
	fclose(f);

}
