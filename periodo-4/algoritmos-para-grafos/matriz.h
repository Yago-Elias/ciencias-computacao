#ifndef _LIST_H

#include <stdbool.h>
#define _LIST_H

#define vertex int

struct graph {
    int V;
    int A;
    int **adj; 
};

typedef struct graph *Graph;

Graph GRAPHinit( int V);
void GRAPHinsertArc( Graph G, vertex v, vertex w);
void UGRAPHinsertArc( Graph G, vertex v, vertex w);
void GRAPHremoveArc( Graph G, vertex v, vertex w);
void UGRAPHremoveArc( Graph G, vertex v, vertex w);
void GRAPHshow( Graph G);
Graph GRAPHrand( int V, int A);
int *UGRAPHdegrees(Graph G);
bool isSink(Graph G, vertex v);
bool isSource(Graph G, vertex v);
void listSink(Graph G);
void listSource(Graph G);
Graph GRAPHrandTounament( int V);
void GRAPHdfs( Graph G);
bool GRAPHreach(Graph G, vertex s, vertex t);
bool GRAPHreachAnxious(Graph G, vertex s, vertex t);

#endif