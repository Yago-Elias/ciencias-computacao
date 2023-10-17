#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char c[21];
	int d;
} carne;

int cmp(const void *a, const void *b) {
	carne c1 = *(carne *)a;
	carne c2 = *(carne *)b;

	return c1.d - c2.d;
}

int main() {
	carne lc[10];
	int n, i;

	while (scanf("%d", &n) != EOF) {
		i = -1;
		while (++i < n)
			scanf("%s%d", lc[i].c, &lc[i].d);
		qsort(lc, n, sizeof(carne), cmp);

		for (i = 0; i < n; ++i)
			printf("%s%c", lc[i].c, i==n-1?'\n':' ');
	}

	return 0;
}