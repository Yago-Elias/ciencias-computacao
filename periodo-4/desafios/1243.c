#include <stdio.h>
#include <string.h>

int main() {
	char *c, p[51];
	int l=0, e=0, a;

	scanf("%[^\n]", p);

	for (c = p; c != NULL; c++) {
		a = 0;
		if (c = p[strcspn(p, " .0123456789")+1]) {
			if (*c != '.' && !isdigit(*c)) {
				a++;
				e++;
			}
			else {

			}
		}
	}

	return 0;
}

