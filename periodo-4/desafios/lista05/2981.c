#include <stdio.h>

int main() {
	unsigned long int c, g, d;

	scanf("%ld%ld", &c, &g);
	d = c / g;
	if (d <= 9)
		printf("A UFSC fecha dia %ld de setembro.\n", d + 21);
	else
		printf("A UFSC fecha dia %ld de outubro.\n", d - 9);

	return 0;
}