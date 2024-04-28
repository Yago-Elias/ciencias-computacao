#include <stdio.h>
#include "f_26.h"

int main() {
    struct Soldado *tabuleiro[8][8] = {NULL};
    struct Soldado peca_b[16];
    struct Soldado peca_p[16];

    int linha, des_linha, i, j;
    char peca, coluna, des_coluna;

    inicializar (tabuleiro, peca_b, peca_p);

    printf("Lance: ");
    scanf("%c%c%d%c%d", &peca, &coluna, &linha, &des_coluna, &des_linha);
    coordenada (linha, coluna, &i, &j);

    interface (tabuleiro);
    return 0;
}