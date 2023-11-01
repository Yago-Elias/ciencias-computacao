#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib/list.h"

#define _VERSAO "1.0"

typedef enum Parametro {
	INVALIDO=1,
	DFS,
	BFS,
	HELP,
	VERSAO
	} parametro;
enum Argumento {
	QL=1,
	QC,
	ALG,
	S,
	T
	};

Graph gerarLabirinto(int l, int c) {
	Graph gph = GRAPHinit(l*c);
	int aux = 0;

	for(int i = 0; i < gph->V; i++){
		if(aux < l-1){
			GRAPHinsertArc(gph, i, i+1);
			GRAPHinsertArc(gph, i+1, i);
			aux++;
		} else{
			aux = 0;
		}
		if(i+l < gph->V){
			GRAPHinsertArc(gph, i, i+l);
			GRAPHinsertArc(gph, i+l, i);
		}
	}
	return gph;
}
void GRAPHremoveParede(Graph gph){
	srand(time(NULL));
	int numRemove, whatRemove, aux;
	for(int i = 0; i < gph->V; i++){
		aux = 0;
		if(GRAPHoutdeg(gph, i) == 0){
			continue;
		}
		numRemove = rand() % GRAPHoutdeg(gph, i);
		for(int j = 0; j < numRemove; j++){
			whatRemove = rand() % GRAPHoutdeg(gph, i);
			for (link a = gph->adj[i]; a != NULL; a = a->next){
				if(whatRemove == aux && GRAPHoutdeg(gph, a->w) > 1){
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
	else if (!strcmp(arg, "u"))
		return S;
	else if (!strcmp(arg, "d"))
		return T;
	
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
		if (argc > 6)
			printf("Parâmetro '%s' inválido\n", argv[6]);
		else
			printf("Parâmetros ausentes\n");
	}
	else if (argc == 2 && opc == INVALIDO) {
		err = INVALIDO;
		printf("Parâmetro '%s' inválido\n", argv[1]);
	}
	else if (argc == 6) {
		int ql, qc, s, t;
		
		ql = digito(argv[QL]);
		qc = digito(argv[QC]);
		s = argumento(argv[S]);
		t = argumento(argv[T]);

		if (ql || qc) {
			err = INVALIDO;
			printf("Parâmetro '%s' não é um valor inteiro\n", argv[ql?1:2]);
		}
		else if (strcmp(argv[ALG], "dfs") && strcmp(argv[ALG], "bfs")) {
			err = INVALIDO;
			printf("Parâmetro '%s' inválido\n", argv[ALG]);
		}
		else if ((s != S && s != T) || (t != S && t != T)) {
			err = INVALIDO;
			s = s == S || s == T;
			printf("Parâmetro '%s' inválido\n", s ? argv[T] : argv[S]);
		}
		else if (s == t) {
			err = INVALIDO;
			printf("Início e fim da busca não podem ser iguiais\n");
		}
	}

	if (err) {
		printf("Tente \"./maze --help\" para mais informações\n");
		exit(err);
	}
}

void run(int argc, char **argv) {
	erro(argc, argv);
	Graph G = gerarLabirinto(atoi(argv[QL]), atoi(argv[QC]));
	GRAPHremoveParede(G);
<<<<<<< HEAD

	if(argumento(argv[ALG]) == DFS) {
		if(argumento(argv[S]) == S) {
			if(GRAPHreach(G, 1, 8))
				GRAPHpath(G, 1, 8);
		}
		else if(argumento(argv[S]) == T) {
			if(GRAPHreach(G, 8, 2))
				GRAPHpath(G, 8, 2);
		}
	}
	else if(argumento(argv[ALG]) == BFS) {
		printf("bfs\n");
=======
	GRAPHshow(G);
	if(argumento(argv[ALG]) == DFS){
		GRAPHdfs(G);
		if(argumento(argv[S]) == S){
			if(GRAPHreach(G, 1, 8)){
				GRAPHpath(G, 1, 8);
			} else{
				printf("Não é acessivel\n");
			}
		}
		if(argumento(argv[S]) == T){
			if(GRAPHreach(G, 8, 2)){
				GRAPHpath(G, 8, 2);
			} else{
				printf("Não é acessivel\n");
			}
		}
	}
	if(argumento(argv[ALG]) == BFS){
		
>>>>>>> 52774f1ca0e8dee4dc203761a92666ce8c86e06c
	}
}
