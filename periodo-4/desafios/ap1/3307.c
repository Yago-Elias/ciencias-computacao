#include <stdio.h>
#include <math.h>
/*
vermelho: raio < 12			R$ 0.09
azul:     12 >= raio <= 15	R$ 0.07
amarelo:  raio > 15			R$ 0.05
*/

int main() {
	int n, a;
	float r, t;

	scanf("%d", &n);

	while (n--) {
		scanf("%d", &a);
		r = sqrt(a / 12.56);
		if (r < 12.0)
			printf("vermelho = R$ %.2f\n", a * 0.09);
		else if (r >= 12.0 && r <= 15.0)
			printf("azul = R$ %.2f\n", a * 0.07);
		else
			printf("amarelo = R$ %.2f\n", a * 0.05);
	}

	return 0;
}
