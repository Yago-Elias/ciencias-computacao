#include <stdio.h>
#define TAM_RES 40
#define TAM_FREQ 11
int main(){
	int opiniao, nivel;
	int respostas[TAM_RES] = {1,2,6,4,8,5,9,7,8,10,1,6,3,8,6,
		10,3,8,2,7,6,5,7,6,5,7,6,8,6,7,5,6,6,5,6,7,5,6,4,8,6,8,10};
	int frequencia[TAM_FREQ] = {0};

	for (opiniao = 0; opiniao < TAM_RES; opiniao++)
		++frequencia[respostas[opiniao]];

	printf("%s%17s\n", "Nivel", "Frequencia");
	for (nivel = 1; nivel <= TAM_FREQ - 1; nivel++)
		printf("%5d%17d\n", nivel, frequencia[nivel]);

	return 0;
}
