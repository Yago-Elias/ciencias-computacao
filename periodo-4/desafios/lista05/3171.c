#include <stdio.h>
#include <stdlib.h>

#define vertex int
#define UGraph Graph

typedef struct graph *Graph;

typedef struct node *link;

struct graph {
	int V; 
	int A; 
	link *adj; 
};

struct node { 
	vertex w; 
	link next; 
};

int cc[1000];

Graph GRAPHinit(int V);
void UGRAPHinsertArc(Graph G, vertex v, vertex w);
static link NEWnode(vertex w, link next);
static void dfsRconComps(UGraph G, vertex v, int id);
int UGRAPHconComps(UGraph G);

int main() {
	int i, n, l, x, y;
	Graph g = NULL;

	scanf("%d%d", &n, &l);
	g = GRAPHinit(n);

	while (l--) {
		scanf("%d%d", &x, &y);
		UGRAPHinsertArc(g, x-1, y-1);
	}

	i = UGRAPHconComps(g);
	printf("%s\n", i == 1 ? "COMPLETO" : "INCOMPLETO");

	return 0;
}

Graph GRAPHinit(int V)
{ 
   Graph G = malloc(sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = malloc(V * sizeof (link));
   for (vertex v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}

static link NEWnode(vertex w, link next)
{ 
	link a = malloc(sizeof (struct node));
	a->w = w; 
	a->next = next;     
	return a;                         
}

void UGRAPHinsertArc(Graph G, vertex v, vertex w) { 
   for (link a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v] = NEWnode( w, G->adj[v]);
   G->adj[w] = NEWnode(v, G->adj[w]);
   G->A++;
}

static void dfsRconComps(UGraph G, vertex v, int id) 
{ 
   cc[v] = id;
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (cc[a->w] == -1) 
         dfsRconComps( G, a->w, id); 
}

int UGRAPHconComps(UGraph G) 
{ 
	int id = 0;
	for (vertex v = 0; v < G->V; ++v) 
		cc[v] = -1;
	for (vertex v = 0; v < G->V; ++v)
		if (cc[v] == -1) 
			dfsRconComps( G, v, id++);
	return id;
}
