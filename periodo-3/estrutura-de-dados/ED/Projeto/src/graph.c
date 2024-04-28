#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "./lib/graph.h"

graph *graphAlloc() {
	graph *grp = malloc(sizeof(graph));

	assert(grp != NULL);

	grp->vertex_amount = 0;
	grp->first_vertex = NULL;
	grp->last_vertex = NULL;

	return grp;
}

void edgeFree(edge *first_edge) {
	edge *ed = NULL, *aux_ed = NULL;

	ed = first_edge;
	while (ed) {
		aux_ed = ed;
		ed = ed->next_edge;
		free(aux_ed);
	}
}

void vertexFree(vertex *first_vertex) {
	vertex *vert = NULL, *aux_vert = NULL;

	vert = first_vertex;
	while (vert) {
		edgeFree(vert->first_edge);
		aux_vert = vert;
		vert = vert->next_vertex;

		free(aux_vert);
	}
}

void graphFree(graph *grp) {
	assert(grp != NULL);
	vertexFree(grp->first_vertex);
	free(grp);
}

int 	graphFindVertexLabelByValue(graph *grp, void *search_value, int (*compar)(void*, void*)) {
	vertex *vert = NULL;

	assert(grp != NULL);

	vert = grp->first_vertex;
	while (vert) {
		if (compar(search_value, vert->value))
			return vert->label;
		vert = vert->next_vertex;
	}

	return -1;
}

void   *graphFindVertex(graph *grp, int vertex_label) {
	vertex *vert = NULL;

	assert(grp != NULL);
	assert(vertex_label >= 0);

	vert = grp->first_vertex;
	while (vert) {
		if (vert->label == vertex_label)
			return vert;

		vert = vert->next_vertex;
	}

	return NULL;
}

void 	graphInsertVertex(graph *grp, void *value) {
	vertex *new_vert = NULL;

	assert(grp != NULL);

	new_vert = malloc(sizeof(vertex));

	assert(new_vert != NULL);

	new_vert->value = value;
	new_vert->label = grp->vertex_amount++;
	new_vert->edges_amount = 0;
	new_vert->first_edge = NULL;
	new_vert->last_edge = NULL;
	new_vert->next_vertex = NULL;

	if (grp->first_vertex == NULL)
		grp->first_vertex = new_vert;
	else
		grp->last_vertex->next_vertex = new_vert;

	grp->last_vertex = new_vert;
}

void	graphRemoveVertex(graph *grp, int vertex_label) {
	vertex *vert = NULL, *prev_vert = NULL;

	assert(grp != NULL);
	assert(vertex_label >= 0);

	vert = grp->first_vertex;

	while (vert) {
		if (vert->label != vertex_label) {
			prev_vert = vert;
			vert = vert->next_vertex;
			continue;
		}

		edgeFree(vert->first_edge);

		for (int i = 0; i < grp->vertex_amount; i++)
			graphRemoveEdge(grp, i, vert->label);

		if (prev_vert == NULL)
			grp->first_vertex = vert->next_vertex;
		else
			prev_vert->next_vertex = vert->next_vertex;

		grp->vertex_amount--;

		free(vert);
		break;
	}
}


void	graphInsertEdge(graph *grp, int origin_label, int destiny_label) {
	edge *new_ed = NULL;
	vertex *origin = NULL, *destiny = NULL;

	assert(grp != NULL);
	assert(origin_label >= 0);
	assert(destiny_label >= 0);

	origin = graphFindVertex(grp, origin_label);
	destiny = graphFindVertex(grp, destiny_label);

	assert(origin != NULL && destiny != NULL);

	new_ed = malloc(sizeof(edge));

	assert(new_ed != NULL);

	new_ed->label = origin->edges_amount++;
	new_ed->origin = origin;
	new_ed->destiny = destiny;
	new_ed->next_edge = NULL;

	if (origin->first_edge == NULL)
		origin->first_edge = new_ed;
	else
		origin->last_edge->next_edge = new_ed;

	origin->last_edge = new_ed;
}

void	graphRemoveEdge(graph *grp, int origin_label, int destiny_label) {
	edge *ed = NULL, *prev_ed = NULL;
	vertex *origin = NULL, *destiny = NULL;

	assert(grp != NULL);
	assert(origin_label >= 0);
	assert(destiny_label >= 0);

	origin = graphFindVertex(grp, origin_label);
	destiny = graphFindVertex(grp, destiny_label);

	assert(origin != NULL && destiny != NULL);

	ed = origin->first_edge;
	while (ed) {
		if (ed->destiny->label != destiny_label) {
			prev_ed = ed;
			ed = ed->next_edge;
			continue;
		}

		if (prev_ed == NULL)
			origin->first_edge = ed->next_edge;
		else
			prev_ed->next_edge = ed->next_edge;

		origin->edges_amount--;
		free(ed);
		break;
	}
}
