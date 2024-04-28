#include <stdio.h>
#define TAM 100

int main() {
	int s[TAM], j;
	
	for(j = 0; j < TAM; j++) /* Define os valores */
		s[j] = 2 + 2 * j;
	printf("%s%13s\n","Elemento", "Valor");
	
	for(j = 0; j < TAM; j++)
		printf("%8d%13d\n", j, s[j]);
	return 0;
}
