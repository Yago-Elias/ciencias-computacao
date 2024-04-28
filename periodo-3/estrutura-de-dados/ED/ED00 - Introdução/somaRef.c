#include <stdio.h>

void soma(int, int, int*);

int main() {
    int x=4, y=5, z;
    
    soma(x, y, &z);
    
    printf("%d + %d = %d\n", x, y, z);
    
    return 0;
}

void soma(int a, int b, int *c) {
    *c = a + b;
}
