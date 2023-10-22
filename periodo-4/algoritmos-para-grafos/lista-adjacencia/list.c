#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "list.h"


static link NEWnode( vertex w, link next);
static void dfsR( Graph G, vertex v);
static void printIndent();
static int visited[1000];

//Parte 1 - Conceitos Básicos

/* A função NEWnode() recebe um vértice w e o endereço next de um nó e devolve
   o endereço a de um novo nó tal que a->w == w e a->next == next. */
static link NEWnode( vertex w, link next) { 
   link a = malloc( sizeof (struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}


/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinit() constrói um
   grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit( int V) { 
   Graph G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = malloc( V * sizeof (link));
   for (vertex v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinsertArc() insere um
   arco v-w no grafo G. A função supõe que v e w são distintos, positivos e
   menores que G->V. Se o grafo já tem um arco v-w, a função não faz
   nada. */
void GRAPHinsertArc( Graph G, vertex v, vertex w) { 
   for (link a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v] = NEWnode( w, G->adj[v]);
   G->A++;
}

void UGRAPHinsertArc(Graph G, vertex v, vertex w) { 
   for (link a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v] = NEWnode( w, G->adj[v]);
   G->adj[w] = NEWnode(v, G->adj[w]);
   G->A++;
}

//Exercício para criação desta função
void GRAPHremoveArc (Graph G, vertex v, vertex w) {
  link p, q = NULL;
    for (p = G->adj[v]; p != NULL; p = p->next) {
      if (p->w == w) {
        if (q == NULL)
          G->adj[v] = p->next;
        else
          q->next = p->next;
        p = NULL;
        free(p);
        return;
      }
      q = p;
    }
}

int GRAPHindeg(Graph ghp, vertex v) {return 0;}

int GRAPHoutdeg(Graph ghp, vertex v) {
   int degree;
   for (link a = G->adj[i]; a != NULL; a = a->next) {
      degree++;
   }
   return degree;
}

void GRAPHshow( Graph G) { 
	
   for (vertex v = 0; v < G->V; ++v){
   		printf( "%2d:", v);
    	for (link a = G->adj[v]; a != NULL; a = a->next) 
    		printf(" %2d", a->w);
    	printf("\n");
	}
}

//Random basic.
//Usar srand()
Graph GRAPHrand( int V, int A) { 
   Graph G = GRAPHinit( V);
   while (G->A < A) {
      vertex v = rand() % V;
      vertex w = rand() % V;
      if (v != w) 
         GRAPHinsertArc( G, v, w);
   }
   return G;
}

//-------------------------Ordenação Topológica--------------
// Recebe uma numeração e um Grafo. E diz se a numerçaão é 
// topologica para o grafo dado.
//
bool isTopoNumbering( Graph G, int topo[]) {
   for (vertex v = 0; v < G->V; ++v) 
      for (link a = G->adj[v]; a != NULL; a = a->next) 
         if (topo[v] >= topo[a->w]) 
            return false;
   return true;
}

// Recebe um Grafo e gera uma numeração topológica caso o grafo seja
// topológico.
int topo[1000];
bool topol( Graph G) { 
   // implementação muito ineficiente...
   vertex v;
   for (v = 0; v < G->V; ++v) topo[v] = -1;
   int cnt = 0;
   while (cnt < G->V) {
      for (vertex v = 0; v < G->V; ++v) 
         if (GRAPHindeg( G, v) == 0 && topo[v] == -1)
            break;
      if (v >= G->V) return false;
      // v é fonte
      topo[v] = cnt++;
      for (link a = G->adj[v]; a != NULL; a = a->next)
         GRAPHremoveArc( G, v, a->w);
   }
   return true;
}

int *UGRAPHdegrees(Graph ghp) {
  if (ghp == NULL) return NULL;

  int *grau = calloc(ghp->V, sizeof(vertex)), v;
  link node = NULL;

  for (v = 0; v < ghp->V; ++v)
    for (node = ghp->adj[v]; node != NULL; node = node->next)
      grau[v]++;

  return grau;
}

bool isSource(Graph G, vertex v){
	int cont = 0;
	for (vertex w = 0; w < G->V; ++w){
		if (w == v)
			continue;
		for (link a = G->adj[w]; a != NULL; a = a->next){
			if(a->w == v){
				cont++;
			}
		}
	}
	if(cont){
		return false;
	} else{
		return true;
	}
}

bool isSink(Graph G, vertex v){
	return G->adj[v] == NULL;
}

void listSource(Graph G){
	for(vertex v = 0; v < G->V; ++v){
		if(isSource(G, v) == true && isSink(G, v) == false){
			printf("%2d\n", v);
		}
	}
}

void listSink(Graph G){
	for(vertex v = 0; v < G->V; ++v){
		if(isSink(G, v) == true && isSource(G, v) == false){
			printf("%2d\n", v);
		}
	}
}


static int cnt;
static int indent = 0;
int pre[1000];
void GRAPHdfs( Graph G) {
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
  for (link a = G->adj[v]; a != NULL; a = a->next) {
    vertex w = a->w;
    if (pre[w] == -1){
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
  for (int i = 0; i < indent; i++)
    printf("-");
}

static void reachR(Graph G, vertex v) {
   visited[v] = 1;
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (visited[a->w] == 0)
         reachR(G, a->w);
}

bool GRAPHreach(Graph G, vertex s, vertex t) {
   for (vertex v = 0; v < G->V; ++v)
      visited[v] = 0;
   reachR(G, s);
   if (visited[t] == 0) return false;

   return true;
}