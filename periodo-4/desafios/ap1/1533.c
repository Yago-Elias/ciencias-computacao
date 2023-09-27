#include <stdio.h>

int main() {
	int n, c, i, s[2], i_s[2];

	while (1) {
		s[0] = 0;
		s[1] = 0;
		i_s[0] = 0;
		i_s[1] = 0;

		scanf("%d", &c);
		if (c == 0) break;

		for (i = 1; i <= c; ++i) {
			scanf("%d", &n);
			if (s[0] < n) {
				s[1] = s[0];
				s[0] = n;
				i_s[1] = i_s[0];
				i_s[0] = i;
			}
			else if (s[0] > n && n > s[1]) {
				s[1] = n;
				i_s[1] = i;
			}
		}

		printf("%d\n", i_s[1]);
	}

	return 0;
}
