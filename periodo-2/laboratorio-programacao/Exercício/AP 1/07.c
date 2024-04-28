#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float desvPadrao(float x[], int n) {
	float soma = 0, media = 0;
	int i;
	
	for (i=0; i<n; i++)
		soma += x[i];
	media = soma/n;
	
	soma = 0;
	for (i=0; i<n; i++) {
		soma += pow(x[i] - media, 2);
	}
	
	return sqrt(soma/n);
}

int main() {
	float x[] = {2,3,5,7,11,13,17};
	printf("s = %f\n", desvPadrao(x, 7));
	return 0;
}
