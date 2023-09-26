#include <stdio.h>
#include "matriz.h"
#include "list.h"

int main()
{
	/*
	Graph ghp = GRAPHinit(5);

	GRAPHinsertArc(ghp, 0, 1);
	GRAPHinsertArc(ghp, 0, 4);
	GRAPHinsertArc(ghp, 1, 2);
	GRAPHinsertArc(ghp, 2, 3);
	GRAPHinsertArc(ghp, 3, 0);
	GRAPHinsertArc(ghp, 4, 1);
	GRAPHinsertArc(ghp, 4, 3);

	GRAPHshow(ghp);
	grau = GRAPHdegrees(ghp);
	for (int i = 0; i < ghp->V; ++i)
		printf(" %d: %dv\n", i, grau[i]);


	int *grau = NULL;
	Graph ghp = GRAPHinit(5);

	UGRAPHinsertArc(ghp, 0, 1);
	UGRAPHinsertArc(ghp, 0, 4);
	UGRAPHinsertArc(ghp, 1, 2);
	UGRAPHinsertArc(ghp, 2, 3);
	UGRAPHinsertArc(ghp, 3, 0);
	UGRAPHinsertArc(ghp, 4, 1);
	UGRAPHinsertArc(ghp, 4, 3);

	GRAPHshow(ghp);

	grau = UGRAPHdegrees(ghp);
	for (int i = 0; i < ghp->V; ++i)
		printf(" %d: %dv\n", i, grau[i]);
	*/

	// ------   VÉRTICE DE S A T   ------ //
	// EXEMPLO A
	Graph ghp = GRAPHinit(10);
	vertex s=0, t=8;

	GRAPHinsertArc(ghp, 0, 1);
	GRAPHinsertArc(ghp, 0, 6);
	GRAPHinsertArc(ghp, 1, 2);
	GRAPHinsertArc(ghp, 1, 4);
	GRAPHinsertArc(ghp, 1, 5);
	GRAPHinsertArc(ghp, 2, 3);
	GRAPHinsertArc(ghp, 6, 7);
	GRAPHinsertArc(ghp, 6, 9);
	GRAPHinsertArc(ghp, 7, 8);

	printf("Existe caminho:\n");
	printf("A: 0 -> 8 | %d\n", GRAPHreach(ghp, s, t));


	// EXEMPLO B
	Graph ghp1 = GRAPHinit(10);

	GRAPHinsertArc(ghp1, 0, 1);
	GRAPHinsertArc(ghp1, 0, 2);
	GRAPHinsertArc(ghp1, 1, 3);
	GRAPHinsertArc(ghp1, 1, 4);
	GRAPHinsertArc(ghp1, 2, 5);
	GRAPHinsertArc(ghp1, 2, 6);
	GRAPHinsertArc(ghp1, 2, 7);
	GRAPHinsertArc(ghp1, 4, 8);
	GRAPHinsertArc(ghp1, 7, 9);

	printf("B: 0 -> 8 | %d\n", GRAPHreach(ghp1, s, t));


	// EXEMPLO C
	Graph ghp2 = GRAPHinit(6);

	GRAPHinsertArc(ghp2, 0, 2);
	GRAPHinsertArc(ghp2, 0, 3);
	GRAPHinsertArc(ghp2, 0, 4);
	GRAPHinsertArc(ghp2, 2, 1);
	GRAPHinsertArc(ghp2, 2, 4);
	GRAPHinsertArc(ghp2, 3, 4);
	GRAPHinsertArc(ghp2, 3, 5);
	GRAPHinsertArc(ghp2, 4, 1);
	GRAPHinsertArc(ghp2, 4, 5);
	GRAPHinsertArc(ghp2, 5, 1);

	printf("C: 0 -> 8 | %d\n", GRAPHreach(ghp2, s, t));
	printf("D: 2 -> 3 | %d\n", GRAPHreach(ghp2, 2, 3));

	// EXERCÍCIO
	printf("E: 0 -> 0 | %d\n", GRAPHreach(ghp2, 0, 0));
	printf("F: 0 -> 4 | %d\n", GRAPHreach(ghp2, 0, 4));

	GRAPHremoveArc(ghp2, 0, 2);
	GRAPHremoveArc(ghp2, 0, 3);
	GRAPHremoveArc(ghp2, 0, 4);
	GRAPHremoveArc(ghp2, 2, 1);
	GRAPHremoveArc(ghp2, 2, 4);
	GRAPHremoveArc(ghp2, 3, 4);
	GRAPHremoveArc(ghp2, 3, 5);
	GRAPHremoveArc(ghp2, 4, 1);
	GRAPHremoveArc(ghp2, 4, 5);
	GRAPHremoveArc(ghp2, 5, 1);
	printf("\nArcos removidos\nF: 0 -> 4 | %d\n", GRAPHreach(ghp2, 0, 4));

	Graph ghp3 = GRAPHinit(6);

	printf("\nNovo grafo\nG: 0 -> 0 | %d\n", GRAPHreach(ghp3, 0, 0));

	printf("H: 2 -> 4 | %d\n", GRAPHreachAnxious(ghp2, 2, 4));

	return 0;
}
