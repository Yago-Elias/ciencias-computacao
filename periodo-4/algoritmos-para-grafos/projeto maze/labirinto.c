#include "../matriz-adjacencia/list.h"

Graph *gerarLabirinto(int v) {
	Graph *gph = GRAPHinit(v);

	for (link li = gph->next; li != NULL; li = li->next) {
		for (link j = 0; j < count; ++j) {
		}
	}

	return gph;
}

void run(int argc, char **argv) {
	printf("%s\n", argv[0]);
}