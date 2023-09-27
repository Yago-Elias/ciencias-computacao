#include <stdio.h>

int main() {
	int n, t, a[50], at;
	char s[51];

	scanf("%d", &n);

	while (n--) {
		scanf("%d", &t);
		at = 0;
		for (int i = 0; i < t; ++i)
			scanf("%d", &a[i]);
		scanf("%s", s);

		for (int i = 0; i < t; ++i) {
			if ((s[i] == 'S' && a[i] <= 2)
			 || s[i] == 'J' && a[i] > 2)
				at++;
		}

		printf("%d\n", at);
	}

	return 0;
}
