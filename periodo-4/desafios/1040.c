#include <stdio.h>

int main() {
	float n1, n2, n3, n4, m;

	scanf("%f%f%f%f", &n1, &n2, &n3, &n4);
	m = (2 * n1 + 3 * n2 + 4 * n3 + n4) / 10;
	printf("Media: %.1f\n", m);

	if (m >= 7.0)
		printf("Aluno aprovado.\n");
	else if (m < 5.0)
		printf("Aluno reprovado.\n");
	else if (m >= 5.0 && m < 7.0) {
		scanf("%f", &n1);
		printf("Aluno em exame.\nNota do exame: %.1f\n", n1);

		if ((m = (n1 + m) / 2) >= 5.0)
			printf("Aluno aprovado.\n");
		else
			printf("Aluno reprovado.\n");
		printf("Media final: %.1f\n", m);
	}

	return 0;
}