#include <stdio.h>
#define DIM 3
#define VAZIO ' '

void mostrar(char s[DIM][DIM]) {
	int i,j;
    printf("   0   1   2\n");
	for (i=0; i < DIM; i++) {
        printf("%d ",i);
        for (j=0; j < DIM; j++)
			printf(" %c %c",s[i][j], j == DIM-1 ? ' ' : '|');
			
        if (i != DIM-1)
			printf("\n  ---+---+---") ;
        printf("\n");
	}
}

int main() {
	char velha[DIM][DIM] = {' ',' ',' ',' ', ' ', ' ',' ',' ',' '};
	int x, y, numeroDeJogadas = 0;
	char simbolo = 'O'; // Simbolo inicial
    while (1) { 
        system("clear"); // apaga o console
		mostrar(velha);	
        printf("\nJogador: %c\nPosição (x y): ", simbolo);
		scanf("%d %d",&x,&y);
		if (velha[x][y] == VAZIO) {
            velha[x][y] = simbolo;
			simbolo = (simbolo == 'O') ? 'X' : 'O';
			numeroDeJogadas++;
		}
		else
			printf("Posição já ocupada\nJogue Novamente!!!\n");
		if (numeroDeJogadas == DIM*DIM) break; /* Finalizar o jogo */
	}
	mostrar(velha);
	return 0;
}
