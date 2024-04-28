#include <stdio.h>
#include "bhaskara.h"

int main() {
    float a = 1, b = 2, c = 1, x1, x2;
    int numR;
    
    numR = bhaskara(a, b, c, &x1, &x2);
    
    if (numR == 2) {
        printf("x1 = %f, x2 = %f\n", x1, x2);
    }
    else if (numR == 1) {
        printf("x1 = %f\n", x1);
    }
    else {
        printf("Nao ha raizes reais\n");
    }
    
    return 0;
}
