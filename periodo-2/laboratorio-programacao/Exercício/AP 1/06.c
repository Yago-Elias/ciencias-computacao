#include <stdio.h>
#include <stdlib.h>

void paresPrimeiro(int v[], int t) {
	int i, p=0, aux;
	for (i=0; i < t; i++) {
		if (v[i] % 2 == 0) {
			aux = v[i];
			v[i] = v[p];
			v[p] = aux;
			p++;
		}
	}
}

int main() {
	int n[] = {3,7,6,9,14,2,1};
	int i;
	
	paresPrimeiro(n, 7);
	
	for (i=0; i < 7; i++)
		printf("%d ", n[i]);
	printf("\n");
	
	return 0;
}







