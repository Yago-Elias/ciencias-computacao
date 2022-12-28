#include <stdio.h>

int main()
{
    int i, number, even=0, odd=0, positive=0, negative=0;

    for (i = 0; i < 5; ++i)
    {
        scanf("%d", &number);
        if (number % 2 == 0) ++even;
        else ++odd;
        if (number > 0) ++positive;
        else if (number < 0) ++negative;
    }
    printf(
        "%d valor(es) par(es)\n"
        "%d valor(es) impar(es)\n"
        "%d valor(es) positivo(s)\n"
        "%d valor(es) negativo(s)\n", 
        even, odd, positive, negative);
}