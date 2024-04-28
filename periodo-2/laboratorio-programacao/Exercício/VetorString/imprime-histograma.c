#include <stdio.h>
#define TAM 10
int main(){
	int n[TAM] = {19,3,15,7,11,9,13,5,17,1};
	int i, j;

	printf("%s%13s%17s\n", "Elemento", "Valor", "Histograma");

	for (i = 0; i <= TAM - 1; i++) {
		printf("%8d%13d       ", i, n[i]);

		for (j = 1; j <= n[i]; j++) /* imprime uma barra */
			printf("%c", '*');

		printf("\n");
	}
	return 0;
}
