#include <stdio.h>

int main() {
	int i, t, c, d, a;
	unsigned long int rc, rd, r;

	scanf("%d", &t);
	while (t--) {
		rc = 1;
		rd = 1;

		scanf("%d%d", &c, &d);
		if (c == 0 && d == 0) {
			printf("0\n");
			continue;
		}

		a = (c > d ? c : d);
		for (i = 0; i < a; ++i) {
			if (i < c)
				rc *= 26;
			if (i < d)
				rd *= 10;
		}
		printf("%ld\n", rc * rd);
	}

	return 0;
}
