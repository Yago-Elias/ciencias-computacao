#include <stdio.h>

int main() {
	int n, m, p, d, s[100] = {0}, r;

	scanf("%d%d", &n, &m);

	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &p, &d);
		
		r = p % d;
		for (int j = 1; j <= n; ++j) {
			if (j % d == r && s[j-1] == 0)
				s[j-1] = 1;
		}
	}

	for (int i = 0; i < n; ++i)
		printf("%d\n", s[i]);

	return 0;
}