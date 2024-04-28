#include <stdio.h>

int potencia(int, int);

int main() {
    int x, y;
    
    printf("Informe 2 valores inteiros\n");
    scanf("%d%d", &x, &y);
    printf("= %d\n", potencia(x, y));
    
    return 0;
}

int potencia(int b, int e) {
    int i, mult = 1;
    
    for (i = 0; i < e; i++) {
        mult = mult * b;
    }
    
    return mult;
}
