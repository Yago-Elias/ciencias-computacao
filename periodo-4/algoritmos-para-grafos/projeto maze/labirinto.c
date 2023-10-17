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

void ajuda() {
	printf(
		"Uso:\n\t./maze ql qc alg s t\n"
		"\tql\t\tnúmero de linhas\n"
		"\tqc\t\tnúmero de colunas\n"
		"\tdfs\t\talgorítimo de busca em profundidade\n"
		"\tdfs\t\talgorítimo de busca em largura\n"
		"\n"
	);
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
