#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RB.h"

int comparInt(const void *a, const void *b) {
    int *n1 = (int*)a;
    int *n2 = (int*)b;
    return *n1 - *n2;
}

void *RB_findOrdem(RB *t, int i) {
    RB_node *p, *next_p;
    int (*compar)(const void *, const void *);
    int cmp_result;
    letras *aux;

    compar = t->compar;

    if ((next_p = t->root)) {
        /* Repeatedly explore either the left or right branch, depending on the
         * value of the key, until the correct item is found.
         */
        do {
            p = next_p;
            aux = p->item;
            cmp_result = compar(&i, &aux->chave);
            if (cmp_result < 0) {
                next_p = p->left;
            }
            else if (cmp_result > 0) {
                next_p = p->right;
            }
            else {
                /* Item found. */
                return p->item;
            }
        } while (next_p);
    }
    return NULL;
}

void printOrdem(RB *tree) {
    letras *aux;
    for (int i = 57; i > 0; i--)
    {
        aux = RB_findOrdem(tree, i);
        printf("%d %s\n", aux->chave, aux->letra);
    }
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
				//printf("%d %s\n", l[i].chave, l[i].letra);
                RB_insert(tree, &l[i]);
            }
        }
    }

    printOrdem(tree);

	return 0;
}