#include <stdio.h>
#include <stdlib.h>

int isPrime(int n) {
	int i;
	
	if (n < 2)
		return 0;
	
	for (i=2; i<n; i++)
		if (n % i == 0)
			return 0;
	
	return 1;
}

int main(int argc, char *argv[]) {
	int n;
	if (argc == 2) {
		n = atoi(argv[1]);
		if (isPrime(n))
			printf("é primo\n");
		else
			printf("não é primo\n");
	}
	return 0;
}




