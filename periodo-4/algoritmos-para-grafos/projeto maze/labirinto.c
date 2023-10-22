#include <stdio.h>
#include "../lista-adjacencia/list.h"

Graph gerarLabirinto(int l, int c) {
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

void run(int argc, char **argv) {
	Graph gph = gerarLabirinto(atoi(argv[1]), atoi(argv[2]));

	if (!strcmp(argv[3], "dfs"))
		GRAPHdfs(gph);
	else
		GRAPHbfs(gph, atoi(argv[4]), atoi(argv[5]))
}
