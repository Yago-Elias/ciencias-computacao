#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../lista-adjacencia/list.h"

#define _VERSAO "1.0"

typedef enum Parametro {INVALIDO=1, DFS, BFS, HELP, VERSAO} parametro;

Graph gerarLabirinto(int u, int d) {
	Graph gph = GRAPHinit(u);

	// for(int i = 0; i < G->V; i++){
	// 	if(i + 1 < 0){
	// 		}
	// }

	return gph;
}

void versao() {
	printf("maze - versão %s - Escrito por Yago Elias e Yuri Venceslau\n", _VERSAO);
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
		"\nDocumentação completa em: <https://github.com/Yago-Elias/ciencias-computacao/periodo-4/algoritmo-para-grafos/projeto-maze/>\n"
	);
}

parametro argumento(char *arg) {
	if (arg == NULL) return INVALIDO;
	else if (!strcmp(arg, "--help") || !strcmp(arg, "--h"))
		return HELP;
	else if (!strcmp(arg, "--version") || !strcmp(arg, "--v"))
		return VERSAO;
	else if (!strcmp(arg, "dfs"))
		return DFS;
	else if (!strcmp(arg, "bfs"))
		return BFS;
	
	return INVALIDO;
}

void erro(int argc, char **argv) {
	parametro err = 0, opc;
	opc = argumento(argv[1]);

	if (argc != 2 && argc != 6) {
		err = INVALIDO;
		ajuda();
	}
	else if (argc == 2 && opc == INVALIDO) {
		err = INVALIDO;
		printf("Parâmetro '%s' inválido\nTente \"./maze --help\" para mais informações\n", argv[1]);
	}
	else if (argc == 6) {
		int ql, qc;
		err = INVALIDO;
		ql = !isdigit(argv[1]) ? 1 : !isdigit(argv[2]) ? 2 : 0;
		printf("%d\n", ql);
		if (ql) printf("Parâmetro '%s' não é um valor inteiro\n", argv[ql]);
	}

	if (err) exit(err);
}

void run(int argc, char **argv) {
	erro(argc, argv);
}
