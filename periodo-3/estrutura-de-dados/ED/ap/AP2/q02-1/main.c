#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RB.h"

int comparInt(const void *a, const void *b) {
    int *n1 = (int*)a;
    int *n2 = (int*)b;
    return *n1 - *n2;
}

//gcc main.c RB.c -c && gcc main.o RB.o && ./a.out

int main()
{
	char pula_linha;
    FILE *f = fopen("letra_musica.txt", "r");
    RB *tree = RB_alloc(comparInt);
	letras l[59];

    if (f)
    {
        for (int i = 0; i < 58; i++)
        {
			if (fscanf(f, "%d%s%c", &l[i].chave, l[i].letra, &pula_linha) == 3) {
				printf("%d %s\n", l[i].chave, l[i].letra);
                RB_insert(tree, &l[i]);
            }
        }
    }



	return 0;
}