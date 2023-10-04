#include <stdio.h>

int main() {
	int x, s;

	while (1) {
		scanf("%d", &x);
		if (x == 0 ) return 0;

		if (x % 2 != 0) x++;
		x = (x + (x + 8)) * 5 / 2;
		printf("%d\n", x);
	}

	return 0;
}
