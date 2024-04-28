#include <stdio.h>
#define TAM 5

void modificaArray(int [], int);
void modificaElemento(int);

int main() {
	int a[TAM] = {0, 1, 2, 3, 4}, i, j;

	printf("Array: { ");
	for (i = 0; i <= TAM - 1; i++)
		printf("%d ", a[i]);
	printf("}\n");

	modificaArray(a, TAM);

	printf("Array: { ");
	for (i = 0; i <= TAM - 1; i++)
		printf("%d ", a[i]);
	printf("}\na[3] = %d\n", a[3]);
	
	modificaElemento(a[3]);
	printf("a[3] = %d\n", a[3]);
	return 0;
}

void modificaArray(int b[], int tamanho){
    int j;
	for (j = 0; j <= tamanho - 1; j++)
		b[j] *= 2;
}

void modificaElemento(int e){
	printf("Valor em modificaElemento = %d\n", e *= 2);
}
