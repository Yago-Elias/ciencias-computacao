#include <stdio.h>
#include <stdlib.h>

int main() {
	float precos[5] = {150.99, 29.9, 1.99, 49.9, 77.8};
	float soma = 0;
	int inf50 = 0, i, sup50 = 0;;
	
	for (i=0; i<5; i++) {
		if (precos[i] <= 50)
			inf50++;
		else {
			sup50++;
			soma += precos[i];
		}
	}
	
	printf("%d produtos <= R$50\n", inf50);
	printf("media %.2f dos produtos > R$50\n", soma/sup50);
	
	return 0;
}
