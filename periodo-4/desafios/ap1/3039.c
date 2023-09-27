#include <stdio.h>

int main() {
	int c, i, f=0;
	char n[30], s;

	scanf("%d", &c);
	for (i = 0; i < c; ++i) {
		scanf("%s %c", n, &s);
		if (s == 'F')
			f++;
	}
	printf("%d carrinhos\n%d bonecas\n", c-f, f);

	return 0;
}
