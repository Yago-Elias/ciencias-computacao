#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int i, soma;
	
	printf("programa: %s\n",argv[0]);

	if(argc == 1)
		printf(" info: nenhum parâmetro.\n");
	
	for(i=1, soma=0; i<argc; i++)
		soma = soma + atoi(argv[i]);
	
	printf(" soma = %d\n",soma);

	return 0;
}
