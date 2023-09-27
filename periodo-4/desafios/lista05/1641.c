#include <stdio.h>
#include <math.h>

int main() {
	int r, w, l, c=1;
	float d, qtd;

	while (1) {
		scanf("%d", &r);
		if (r == 0) break;

		scanf("%d%d", &w, &l);
		d = w * w + l * l;
		d = sqrt(d);
		if ((2 * r / d) >= 1.0)
			printf("Pizza %d fits on the table.\n", c);
		else
			printf("Pizza %d does not fit on the table.\n", c);
		c++;
	}

	return 0;
}
