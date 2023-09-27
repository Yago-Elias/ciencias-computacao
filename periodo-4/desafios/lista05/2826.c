#include <stdio.h>
#include <string.h>

int main() {
	char p1[21], p2[21];

	scanf("%s%s", p1, p2);

	if (strcmp(p1, p2) < 0)
		printf("%s\n%s\n", p1, p2);
	else
		printf("%s\n%s\n", p2, p1);

	return 0;
}