#include <stdio.h>
#include <stdlib.h>

int main() {
	int p, n, ca, pc;

	scanf("%d%d", &p, &n);

	scanf("%d", &pc);
	while (--n) {
		ca = pc;
		scanf("%d", &pc);
		if (p < abs(ca - pc)) {
			printf("GAME OVER\n");
			return 0;
		}
	}
	printf("YOU WIN\n");

	return 0;
}
