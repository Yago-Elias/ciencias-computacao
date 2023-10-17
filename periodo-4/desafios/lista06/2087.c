#include <stdio.h>

int main() {
	int s, t, f, c;

	scanf("%d%d%d", &s, &t, &f);
	c = ((s + t + f) % 24);
	printf("%d\n", c >= 0 ? c : c + 24);

	return 0;
}
