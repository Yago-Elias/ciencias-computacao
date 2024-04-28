#include <stdio.h>
#include <math.h>

struct Ponto
{
	int y;
	int x;
} ponto;

int main()
{
	float d;

	printf ("Digite um ponto cartesiano: ");
	scanf ("%d%d", &ponto.x, &ponto.y);
	
	d = sqrt (pow(ponto.x, 2) + pow (ponto.y, 2));
	printf ("A distância é: %.2f\n", d);
	return 0;
}