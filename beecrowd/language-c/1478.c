#include <stdio.h>

#define TAM 5

int main()
{
    int i, j, line;

    for (i = 1; i < TAM; ++i)
    {
        line = i;
        for (j = 1; j < TAM; ++j)
        {
            printf("% 2d", line);
            if (line <= i && line > 1) --line;
            else ++line;
        }
        printf("\n");
    }
    return 0;
}