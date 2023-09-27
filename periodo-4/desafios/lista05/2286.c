#include <stdio.h>

int main() {
	int n, a, b, c=0;
	char j1[11], j2[11];

	while (++c) {
		scanf("%d", &n);
		if (n == 0) return 0;
		printf("Teste %d\n", c);
		scanf("%s%s", j1, j2);

		while (n--) {
			scanf(" %d%d", &a, &b);
			printf("%s\n", (a+b)%2==0?j1:j2);
		}
		printf("\n");
	}
	return 0;
}