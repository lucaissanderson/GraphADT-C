#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#endif

#include "List.h"

/* define NIL and INF */
#define NIL 0
#define INF -1

/* enumerate colors */
enum colors { white, grey, black };

/* define GraphObj and Graph*/
typedef struct GraphObj {
    List* neighbors;
    int* color;
    int* parent;
    int* distance;
    int order;
    int edges;
    int source;
} GraphObj;

typedef GraphObj* Graph;

/* Constructors/Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);

/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

/* Manipulation procedures */
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

/* other operations */
void printGraph(FILE* out, Graph G);


