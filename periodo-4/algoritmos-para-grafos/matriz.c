#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "matriz.h"


static int **MATRIXint( int r, int c, int val);
static void dfsR( Graph G, vertex v);
static void printIndent();
static int visited[10000];


static int **MATRIXint( int r, int c, int val) { 
    int **m = malloc( r * sizeof (int *));
    for (vertex i = 0; i < r; ++i) 
        m[i] = malloc( c * sizeof (int));
    for (vertex i = 0; i < r; ++i)
        for (vertex j = 0; j < c; ++j)
            m[i][j] = val;
    return m;
}

Graph GRAPHinit( int V) { 
    Graph G = malloc( sizeof *G);
    G->V = V; 
    G->A = 0;
    G->adj = MATRIXint( V, V, 0);
    return G;
}

void GRAPHinsertArc( Graph G, vertex v, vertex w) { 
    if (G->adj[v][w] == 0) {
        G->adj[v][w] = 1; 
        G->A++;
    }
}

void UGRAPHinsertArc( Graph G, vertex v, vertex w) { 
    if (G->adj[v][w] == 0) {
        G->adj[v][w] = 1; 
        G->adj[w][v] = 1; 
        G->A++;
    }
}

void GRAPHremoveArc( Graph G, vertex v, vertex w) {
    if (G->adj[v][w] == 1) {
        G->adj[v][w] = 0;
        G->A--;
    }
}

void UGRAPHremoveArc( Graph G, vertex v, vertex w) {
    if (G->adj[v][w] == 1) {
        G->adj[v][w] = 0;
        G->adj[w][v] = 0;
        G->A--;
    }
}


void GRAPHshow( Graph G) { 
    for (vertex v = 0; v < G->V; ++v) {
        printf( "%2d:", v);
        for (vertex w = 0; w < G->V; ++w) {
            if (G->adj[v][w] == 1) 
                printf( " %2d", w);
        }
        printf( "\n");
    }
}

Graph GRAPHrand( int V, int A) { 
    Graph G = GRAPHinit( V);
    srand(1);
    while (G->A < A) {
        vertex v = rand() % V;
        vertex w = rand() % V;
        if (v != w) 
            GRAPHinsertArc( G, v, w);
    }
    return G;
}

int *UGRAPHdegrees(Graph ghp) {
    int *grau = calloc(ghp->V, sizeof(vertex));

    for (int i = 0; i < ghp->V; ++i)
        for (int j = 0; j < ghp->V; ++j) {
            if (ghp->adj[i][j] == 1)
                grau[i]++;
        }

    return grau;
}

bool isSink(Graph G, vertex v) {
    int cont = 0;
    for(int i = 0; i < G->V; i++) {
        if(G->adj[v][i] == 1)
    		cont++;
    }

    return (cont ? false : true);
}

bool isSource(Graph G, vertex v) {
	int cont = 0;
	for(int i = 0; i < G->V; i++) {
		if(G->adj[i][v] == 1)
			cont++;
    }

    return (cont ? false : true);
}

void listSink(Graph G) {
	for(vertex i = 0; i < G->V; i++) {
		if(isSink(G, i) == true)
			printf("%2d\n", i);
    }
}

void listSource(Graph G) {
	for(vertex i = 0; i < G->V; i++) {
		if(isSource(G, i) == true)
			printf("%2d\n", i);
    }
}

static int cnt;
static int indent = 0;
int pre[1000];

void GRAPHdfs(Graph G) {
    cnt = 0;

    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;

    for (vertex v = 0; v < G->V; ++v) {
        if (pre[v] == -1) {
            printf("%d dfsR(G, %d)\n", v, v);
            dfsR( G, v); // começa nova etapa
            printf("%d\n", v);
        }
    }
}

static void dfsR( Graph G, vertex v) {
    pre[v] = cnt++;
    for (vertex w = 0; w < G->V; w++) {
        if (G->adj[v][w] != 1)
         continue;

        if (pre[w] == -1) {
            printIndent();
            printf("%d-%d dfsR(G, %d)\n", v, w, w);
            indent += 2;
            dfsR( G, w);
        }
        printIndent();
        printf("%d\n", w);
        indent -= 2;
    }
}

static void printIndent() {
    for (int i = 0; i < indent; i+=2)
        printf(" -");
}

static void reachR(Graph G, vertex v) {
    visited[v] = 1;
    for (vertex w = 0; w < G->V; ++w){
        if (G->adj[v][w] == 1 && visited[w] == 0)
            reachR(G, w);
    }
}

bool GRAPHreach(Graph G, vertex s, vertex t) {
    for (vertex v = 0; v < G->V; ++v)
        visited[v] = 0;
    reachR(G, s);
    if (visited[t] == 0) return false;

    return true;
}

static void reachRAnxious(Graph G, vertex v, vertex t) {
    visited[v] = 1;
    for (vertex w = 0; w < G->V; ++w) {
        if (G->adj[v][w] == 1 && visited[w] == 0) {
            printf("[%d, %d]\n", v, w);
            if (w == t) {
                visited[w] = 1;
                break;
            }
            reachRAnxious(G, w, t);
        }
    }
}

bool GRAPHreachAnxious(Graph G, vertex s, vertex t) {
    for (vertex v = 0; v < G->V; ++v)
        visited[v] = 0;
    reachRAnxious(G, s, t);
    if (visited[t] == 0) return false;

    return true;
}
