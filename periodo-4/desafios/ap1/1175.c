#include <stdio.h>

int main() {
	int v[20]	;

	for (int i = 0; i < 20; ++i)
		scanf("%d", &v[i]);

	for (int i = 0; i < 20; ++i)
		printf("N[%d] = %d\n",i,  v[19-i]);

	return 0;
}
