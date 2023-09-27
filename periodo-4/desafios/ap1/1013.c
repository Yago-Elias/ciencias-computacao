#include <stdio.h>
#include <stdlib.h>

int maiorAB(int a, int b) {
	return (a+b+abs(a-b)) / 2;
}

int main() {
	int a, b, c;

	scanf("%d%d%d", &a, &b, &c);
	a = maiorAB(a, b);
	printf("%d eh o maior\n", maiorAB(a, c));

	return 0;
}
