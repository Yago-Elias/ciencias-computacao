#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

/* Vértices de grafos são representados por objetos do tipo vertex. */
#define vertex int

/* A lista de adjacência de um vértice v é composta por nós do tipo node. Cada
   nó da lista corresponde a um arco e contém um vizinho w de v e o endereço
   do nó seguinte da lista. Um link é um ponteiro para um node. */
typedef struct node *link;
struct node { 
   vertex w; 
   link next; 
};

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A estrutura graph representa um
   grafo. O campo adj é um ponteiro para o vetor de listas de adjacência, o
   campo V contém o número de vértices e o campo A contém o número de arcos
   do grafo. */
struct graph {
   int V; 
   int A; 
   link *adj; 
};

/* Um Graph é um ponteiro para um graph. */
typedef struct graph *Graph;

Graph GRAPHinit(int V);
void GRAPHinsertArc(Graph G, vertex v, vertex w); 
void UGRAPHinsertArc(Graph G, vertex v, vertex w);
void GRAPHremoveArc(Graph G, vertex v, vertex w);
int GRAPHindeg(Graph ghp, vertex v);
int GRAPHoutdeg(Graph ghp, vertex v);
void GRAPHshow(Graph G);
Graph GRAPHrand(int V, int A);
bool isTopoNumbering(Graph G, int topo[]);
bool topol(Graph G);
int *UGRAPHdegrees(Graph ghp);
int GRAPHtypeTree(Graph ghp);
bool isSink(Graph G, vertex v);
bool isSource(Graph G, vertex v);
void listSink(Graph G);
void listSource(Graph G);
Graph GRAPHrandTounament(int V);
void GRAPHdfs(Graph G);
bool GRAPHreach(Graph G, vertex s, vertex t);
void DAGspt(Dag G, vertex *vv, vertex s, vertex *pa, int *dist);

#endif