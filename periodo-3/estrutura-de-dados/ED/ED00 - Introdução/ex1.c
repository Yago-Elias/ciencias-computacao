#include <stdio.h>

int somaPares(int, int);

int main() {
    int x, y;
    
    printf("Informe 2 valores inteiros\n");
    scanf("%d%d", &x, &y);
    printf("= %d\n", somaPares(x, y));
    
    return 0;
}

int somaPares(int a, int b) {
    int i, soma = 0;
    
    for (i = a; i <= b; i++) {
        if (i % 2 == 0) {
            soma += i;
        }
    }
    
    return soma;
}
