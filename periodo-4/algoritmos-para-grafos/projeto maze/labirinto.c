#include <stdio.h>
#include "../lista-adjacencia/list.h"

Graph gerarLabirinto(int u, int d) {
	Graph gph = GRAPHinit(v);

	// for(int i = 0; i < G->V; i++){
	// 	if(i + 1 < 0){
	// 		}
	// }

	return gph;
}

void run(int argc, char **argv) {
	Graph gph = gerarLabirinto(atoi(argv[1]), atoi(argv[2]));

	if (!strcmp(argv[3], "dfs"))
		GRAPHdfs(gph);
	else
		GRAPHbfs(gph, atoi(argv[4]), atoi(argv[5]))
}
