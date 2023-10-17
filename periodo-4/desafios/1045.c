#include <stdio.h>

int main() {
	float A, B, C, a;

	scanf("%f%f%f", &A, &B, &C);
	
	if (B > A) {
		a = A;
		A = B;
		B = a;
	}
	if (B < C) {
		a = C;
		C = B;
		B = a;
	}
	if (B > A) {
		a = A;
		A = B;
		B = a;
	}

	if (A >= (C + B))
		printf("NAO FORMA TRIANGULO\n");
	else {
		if (A * A == (B * B + C * C))
			printf("TRIANGULO RETANGULO\n");
		if (A * A > (B * B + C * C))
			printf("TRIANGULO OBTUSANGULO\n");
		if (A * A < (B * B + C * C))
			printf("TRIANGULO ACUTANGULO\n");
		if (A == B && B == C)
			printf("TRIANGULO EQUILATERO\n");
		if ((A == B && A != C) || (A == C && A != B) || (B == C && B != A))
			printf("TRIANGULO ISOSCELES\n");
	}

	return 0;
}
