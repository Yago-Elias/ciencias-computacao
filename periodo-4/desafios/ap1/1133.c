#include <stdio.h>

int main() {
	int x, y, a;

	scanf("%d%d", &x, &y);
	if (x > y) {
		a = x;
		x = y;
		y = a;
	}
	for (int i = ++x; i < y; ++i)
		if (i % 5 == 2 || i % 5 == 3)
			printf("%d\n", i);

	return 0;
}
