#include <stdio.h>
#include "../matriz.h"

int main() {
	int a, x, y;
	Graph g = GRAPHinit(10);

	scanf("%d", &a);
	while (a--) {
		scanf("%d%d", &x, &y);
		UGRAPHinsertArc(g, x, y);
	}

	GRAPHbfs(g, 0);
	GRAPHshowNum(g);

	return 0;
}
