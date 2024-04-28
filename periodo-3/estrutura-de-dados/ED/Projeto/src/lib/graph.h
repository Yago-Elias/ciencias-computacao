typedef struct graph graph;
typedef struct vertex vertex;
typedef struct edge edge;


struct graph {
	int 	vertex_amount;
	vertex *first_vertex;
	vertex *last_vertex;
};
struct vertex {
	void   *value;
	int 	label;
	int 	edges_amount;
	edge   *first_edge;
	edge   *last_edge;
	vertex *next_vertex;
};
struct edge {
	int 	label;
	vertex *origin;
	vertex *destiny;
	edge   *next_edge;
};


graph  *graphAlloc();
void	graphFree(graph *grp);

int 	graphFindVertexLabelByValue(graph *grp, void *search_value, int (*compar)(void*, void*));
void   *graphFindVertex(graph *grp, int vertex_label);
void 	graphInsertVertex(graph *grp, void *value);
void	graphRemoveVertex(graph *grp, int vertex_label);

void	graphInsertEdge(graph *grp, int origin_label, int destiny_label);
void	graphRemoveEdge(graph *grp, int origin_label, int destiny_label);
