#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lista-adjacencia/list.h"

Graph gerarLabirinto(int u, int d) {
	Graph gph = GRAPHinit(u);

	// for(int i = 0; i < G->V; i++){
	// 	if(i + 1 < 0){
	// 		}
	// }

	return gph;
}

int erro(int argc, char **argv) {
	return 1;
}

void run(int argc, char **argv) {
	Graph gph = gerarLabirinto(atoi(argv[1]), atoi(argv[2]));

	if (!strcmp(argv[3], "dfs"))
		GRAPHdfs(gph);
	else
		GRAPHbfs(gph, 0);
}
