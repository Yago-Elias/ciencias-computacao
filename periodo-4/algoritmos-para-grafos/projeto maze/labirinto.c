#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef LAB_H
#define LAB_H

#define parede 0
#define avanco 1
#define RST_COLOR "\033[m"
#define BRIGHT_BLUE "\033[1;94m"
#define BRIGHT_RED "\033[1;91m"
#define BRIGHT_GREEN "\033[1;92m"
#define YELLOW "\033[93m"

int **gerarLabirinto(int linha, int coluna) {
	int i, l, c;
	int **lab = malloc(linha * sizeof(int *));
	for (int i = 0; i < linha; ++i)
		lab[i] = calloc(coluna, sizeof(int));

	srand(time(NULL));
	for (i = 0; i < linha * coluna; ++i) {
		l = rand() % linha;
		c = rand() % coluna;
		lab[l][c] = 1;
	}

	return lab;
}

void printLabirinto(int **labirinto, int linha, int coluna) {
	for (int i = 0; i < linha; ++i) {
		for (int j = 0; j < coluna; ++j) {
			// printf("%d ", labirinto[i][j]);
			printf("\033[33m         ");
			if (labirinto[i][j] == parede)
				printf("\033[33m         ");
			else
				printf("%s%s", BRIGHT_GREEN, RST_COLOR);
		}
		printf("\n");
	}
}

#endif
