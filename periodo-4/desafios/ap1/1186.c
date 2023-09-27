#include <stdio.h>

int main() {
	float n, s=0, c=0;
	char o;

	scanf("%c", &o);
	for (int i = 0; i < 12; ++i)
		for (int j = 0; j < 12; ++j) {
			scanf("%f", &n);
			if (i + j > 11) {
				s += n;
				c++;
			}
		}

	printf("%.1f\n", o=='S'?s:s/c);

	return 0;
}
