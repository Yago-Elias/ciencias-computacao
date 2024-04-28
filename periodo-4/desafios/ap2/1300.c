#include <stdio.h>

int main() {
    int a;

    while (scanf("%d", &a) != EOF)
        printf("%s\n", a % 6 == 0 ? "Y" : "N");

    return 0;
} 