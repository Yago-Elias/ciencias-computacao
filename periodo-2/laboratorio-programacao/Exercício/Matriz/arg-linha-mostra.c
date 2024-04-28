#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int i;
	
	printf("programa: %s\n",argv[0]);

	if(argc == 1)
		printf(" info: nenhum parâmetro.\n");
	
	for(i=1; i<argc; i++)
		printf(" parametro [%d]: %s\n", i, argv[i]);

	return 0;
}
