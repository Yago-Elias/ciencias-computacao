#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
	int numCaracteres = 0;	
	
	FILE *f = fopen(argv[1],"r");
	
	while (fgetc(f) != EOF) /* Ler um char */
		numCaracteres++;
	
	fclose(f);
	printf("total de caracteres: %d\n", numCaracteres);
	
	return 0;
}
