#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
	return (* (int *) b) - (* (int *) a);
}

int main() {
	int n, m, pi[1000], pis[1000], c;

	scanf("%d", &n);

	while (n--) {
		c = 0;

		scanf("%d", &m);
		for (int i = 0; i < m; ++i) {
			scanf("%d", &pi[i]);
			pis[i] = pi[i];
		}
		qsort(pis, m, sizeof(int), cmp);

		for (int i = 0; i < m; ++i) {
			if (pi[i] == pis[i])
				c++;
		}

		printf("%d\n", c);
	}

	return 0;
}
