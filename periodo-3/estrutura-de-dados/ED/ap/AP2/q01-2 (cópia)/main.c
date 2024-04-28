#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Queue.h"
#include "AVL.h"
#define tam 100

int comparInt(const void *a, const void *b) {
    int *n1 = (int*)a;
    int *n2 = (int*)b;
    return *n1 - *n2;
}

void printTreeInt(AVL_node *tree) {
    int *n;
    if (tree) {
        n = (int*) tree->item;
        printf("(%d ", *n);
        printTreeInt(tree->left);
        printTreeInt(tree->right);
        printf(") ");
    }
    else
		printf("~ ");
}

void preencheAVL(AVL *tree, Queue * q) {
	int aux;
    for (int i = 0; i < tam; i++){
    	aux = Queue_pop(q);
    	//printf("%d\n", aux);
        AVL_insert(tree, &aux);
    }
}

//gcc main.c Queue.c AVL.c -c && gcc AVL.o main.o Queue.o && ./a.out

int main() {
	Queue *q = Queue_alloc(tam);
	AVL *treeAVL = AVL_alloc( comparInt );
	int aleatorio;
	srand(time(NULL));
	
	for (int i = 0; i < tam; i++)
	{
		aleatorio = (rand() % 100) + 1;
		Queue_push(q, aleatorio);
	}
	
	Queue_print(q);

	preencheAVL(treeAVL, q);

	printTreeInt(treeAVL->root);
	
	//Queue_free(q);
	return 0;
}