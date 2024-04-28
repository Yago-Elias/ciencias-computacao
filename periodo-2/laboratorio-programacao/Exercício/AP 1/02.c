#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define T 15

int isPrime(int n) {
	int i;
	
	if (n < 2)
		return 0;
	
	for (i=2; i<n; i++)
		if (n % i == 0)
			return 0;
	
	return 1;
}

void separaPrimos(int A[T], int B[T]) {
	int i, j=0;
	for (i=0; i<T; i++) {
		
		if (isPrime(A[i])) {
			B[j] = A[i];
			j++;
		}
		
	}
}


int main() {
	int A[T], B[T] = {0}, i;
	
	srand(time(NULL));	
	
	for (i=0; i<T; i++) {
		A[i] = rand() % 200;
		printf("%d ", A[i]);
	}
	printf("\n");	
	
	separaPrimos(A, B);
	
	for (i=0; i<T; i++) {
		if (B[i] == 0)
			break;
		
		printf("%d ", B[i]);
	}
	printf("\n");
	return 0;
}




