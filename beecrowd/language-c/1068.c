#include <stdio.h>

int main()
{
    int i, amount_odd=0, number;

    scanf("%d", &number);
    for (i = number; amount_odd < 6; ++i)
        if (i % 2 != 0)
        {
            printf("%d\n", i);
            ++amount_odd;
        }
    return 0;
}