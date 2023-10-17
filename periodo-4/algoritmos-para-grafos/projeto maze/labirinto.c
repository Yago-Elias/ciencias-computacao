#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lista-adjacencia/list.h"

#define VERSAO "1.0"

Graph gerarLabirinto(int u, int d) {
	Graph gph = GRAPHinit(u);

	// for(int i = 0; i < G->V; i++){
	// 	if(i + 1 < 0){
	// 		}
	// }

	return gph;
}

void versao() {
	printf("%s\n", VERSAO);
}

void ajuda() {
	printf(
		"Uso: ./maze ql qc alg s t\n"
		"  ql\t\t\tnúmero de linhas\n"
		"  qc\t\t\tnúmero de colunas\n"
		"  alg:\n"
		"    dfs\t\t\talgorítimo de busca em profundidade\n"
		"    bfs\t\t\talgorítimo de busca em largura\n"
		"  s\t\t\tvértice de origem para a busca\n"
		"  t\t\t\tvértice de destino para a busca\n"
		"  --v, --version\texibe a versão atual do programa\n"
		"  --h, --help\t\texibe esta ajuda\n"
		"\nDocumentação completa em: <https://github.com/Yago-Elias/ciencias-computacao/periodo-4/algoritmo-para-grafos/projeto-maze>\n"
	);
}

int erro(int argc, char **argv) {
	return 1;
}

void run(int argc, char **argv) {
	Graph gph = gerarLabirinto(atoi(argv[1]), atoi(argv[2]));

	ajuda();
	versao();

	if (!strcmp(argv[1], "--h") || !strcmp(argv[1], "--help"))
		GRAPHdfs(gph);
	else
		GRAPHbfs(gph, 0);
}
