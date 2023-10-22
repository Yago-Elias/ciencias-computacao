#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lista-adjacencia/list.h"
#define _VERSAO "1.0"

typedef enum Parametro {INVALIDO=1, DFS, BFS, HELP, VERSAO} parametro;
enum Argumento {QL=1, QC, ALG, S, T};

Graph gerarLabirinto(int u, int d) {
	Graph gph = GRAPHinit(u);

	Graph gph = GRAPHinit(l*c);
	int aux = 0;

	for(int i = 0; i < gph->V; i++){
		if(aux < l-1){
			UGRAPHinsertArc(gph, i, i+1);
			aux++;
		} else{
			aux = 0;
		}
		if(i+l > gph->V){
			UGRAPHinsertArc(gph, i, i+1+l);
		}
	}
	return gph;
}
void GRAPHremoveParede(Graph gph){
	int numRemove, whatRemove, aux;
	for(int i = 0; i < gph->V; i++){
		aux = 0;
		numRemove = rand % GRAPHoutdeg(gph, i);
		for(int j = 0; j < numRemove; j++){
			whatRemove = rand % GRAPHoutdeg(gph, i);
			for (link a = gph->adj[v]; a != NULL; a = a->next){
				if(whatRemove == aux){
					GRAPHremoveArc(gph, i, a->w);
					GRAPHremoveArc(gph, a->w, i);
				}
				aux++;
			}
		}
	}
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

static int digito(char *arg) {
	for (size_t i = 0; i < strlen(arg); i++)
		if (arg[i] >= '0' && arg[i] <= '9')
			continue;
		else
			return INVALIDO;
	return 0;
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
		
		ql = digito(argv[QL]);
		qc = digito(argv[QC]);
		if (ql || qc) {
			err = INVALIDO;
			printf("Parâmetro '%s' não é um valor inteiro\n", argv[ql?1:2]);
		}

		if (strcmp(argv[ALG], "dfs") && strcmp(argv[ALG], "bfs")) {
			err = INVALIDO;
			printf("Parâmetro '%s' inválido\n", argv[ALG]);
		}
	}

	if (err) {
		printf("Tente \"./maze --help\" para mais informações\n");
		exit(err);
	}
}

void run(int argc, char **argv) {
	erro(argc, argv);
}
