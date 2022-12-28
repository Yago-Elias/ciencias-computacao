#include <stdio.h>

int main()
{
    float number, sum=0, average_positive;
    int i, amount_positive=0;

    for (i = 0; i < 6; i++)
    {
        scanf("%f", &number);
        if (number >= 0)
        {
            ++amount_positive;
            sum += number;
        }
    }
    average_positive = sum / amount_positive;
    printf("%d valores positivos\n%.1f\n", amount_positive, average_positive);
    return 0;
}
