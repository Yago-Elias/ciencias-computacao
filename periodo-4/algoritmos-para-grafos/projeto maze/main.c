#include <stdio.h>
#include "../matriz-adjacencia/matriz.h"
#include "labirinto.c"

int main() {
	int **lab = gerarLabirinto(4, 4);

	printLabirinto(lab, 4, 4);

	return 0;
}