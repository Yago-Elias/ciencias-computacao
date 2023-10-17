#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	float x, y, q;
	scanf("%f%f", &x, &y);

	q = x != 0 ? atan(y / x) : 0;
	printf("%.2f\n", q);
	if (x == 0 && y == 0)
		printf("Origem\n");
	else if (x == 0 && abs(y) > 0)
		printf("Eixo Y\n");
	else if (y == 0 && abs(x) > 0)
		printf("Eixo X\n");
	else if (q <= 90.0 || q <= -270.0)
		printf("Q1\n");
	else if (q <= 180.0 || q <= -180.0)
		printf("Q2\n");
	else if (q <= 270.0 || q <= -90.0)
		printf("Q3\n");
	else
		printf("Q4\n");

	return 0;
}