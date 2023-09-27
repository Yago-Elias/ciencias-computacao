#include <stdio.h>

int main ()
{
	int c1, c2, c3, c4, c5, c6, c7;
	float point_x, point_y;
	scanf("%f%f", &point_x, &point_y);

	if (point_x == point_y && point_y == 0.0) // ponto da origem
		printf("Origem\n");
	else if (point_x > 0.0 && point_y > 0.0) // 1° quadrante
		printf("Q1\n");
	else if (point_x < 0.0 && point_y > 0.0) // 2° quadrante
		printf("Q2\n");
	else if (point_x < 0.0 && point_y < 0.0) // 3° quadrante
		printf("Q3\n");
	else if (point_x > 0.0 && point_y < 0.0) // 4° quadrante
		printf("Q4\n");
	else if (point_x == 0.0 && point_y != 0.0) // eixo point_y
		printf("Eixo Y\n");
	else // eixo x
		printf("Eixo X\n");

	return 0;
}