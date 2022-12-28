#include <stdio.h>

int main()
{
    int i, number, amount_even=0;

    for (i = 0; i < 5; ++i)
    {
        scanf("%d", &number);
        if (number % 2 == 0)
            ++amount_even;
    }
    printf("%d valores pares\n", amount_even);
    return 0;
}
