#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Queue.h"
#include "BST.h"
#define tam 100

int comparInt(const void *a, const void *b) {
    int *n1 = (int*)a;
    int *n2 = (int*)b;
    return *n1 - *n2;
}
/*
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
*/
void preencheBST(BST *tree, Queue * q) {
	int aux;
    for (int i = 0; i < tam; i++){
    	aux = Queue_pop(q);
    	//printf("%d\n", aux);
        BST_insert(tree, aux);
    }
}

void BST_ordena(BST *bst, Queue * q2) {
    if (bst) {
        BST_ordena(bst->left, q2);
        Queue_push(q2, bst->value);
        //printf("%d ", bst->value);
        BST_ordena(bst->right, q2);
        Queue_push(q2, bst->value);
        //printf("%d ", bst->value);
    }
}

//gcc main.c Queue.c BST.c -c && gcc BST.o main.o Queue.o && ./a.out

int main() {
	Queue *q = Queue_alloc(tam);
	BST *tree = BST_alloc();
	int aleatorio;
	srand(time(NULL));
	
	for (int i = 0; i < tam; i++)
	{
		aleatorio = (rand() % 100) + 1;
		Queue_push(q, i);
	}
	
	Queue_print(q);

	preencheBST(tree, q);

    Queue *q2 = Queue_alloc(tam);

	BST_ordena(tree, q2);

    printf("Fila em Ordem\n");
    Queue_print(q2);
	
	//Queue_free(q);
	return 0;
}