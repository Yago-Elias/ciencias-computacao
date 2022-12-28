#include <stdio.h>

int main()
{
    int number1, number2;

    scanf("%d%d", &number1, &number2);
    if (number1 % number2 == 0 || number2 % number1 == 0)
        printf("Sao Multiplos\n");
    else
        printf("Nao sao Multiplos\n");
    return 0;
}
