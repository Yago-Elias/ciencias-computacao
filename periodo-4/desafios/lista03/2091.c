#include <stdio.h>

int main()
{
	int q;
	long long int n = 0, x;

	while (1) {
		scanf("%d", &q);
		if (!q) break;

		while (q--) {
			scanf(" %lld", &x);
			n ^= x;
		}

		printf("%lld\n", n);
	}

	return 0;
}
