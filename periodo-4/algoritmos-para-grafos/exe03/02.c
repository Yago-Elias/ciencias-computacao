#include <stdio.h>
#include "../matriz.h"

int main() {
	int a, x, y;
	Graph g = GRAPHinit(8);

	scanf("%d", &a);
	while (a--) {
		scanf("%d%d", &x, &y);
		UGRAPHinsertArc(g, x, y);
	}

	printf("BFS pelo vértice 0\n");
	GRAPHbfs(g, 0);
	GRAPHshowNum(g);

	printf("\nBFS pelo vértice 4\n");
	GRAPHbfs(g, 4);
	GRAPHshowNum(g);

	return 0;
}
