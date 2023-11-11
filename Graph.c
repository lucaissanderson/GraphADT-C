/***************************
*  pa2 : Graph.c
*  Lucais Sanderson
*  lzsander
***************************/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

/* Constructors/Destructors */
// allocate and create memory for graph
Graph newGraph(int n){
    Graph g = malloc(sizeof(GraphObj));
    g->color = calloc(n+1, sizeof(int));
    g->parent = calloc(n+1, sizeof(int));
    g->distance = calloc(n+1, sizeof(int));
    g->neighbors = calloc(n+1, sizeof(List*));
    for(int i = 1; i <= n; i++){
        g->color[i] = white;
        g->parent[i] = NIL;
        g->distance[i] = INF;
        g->neighbors[i] = newList();
    }
    g->order = n;
    g->edges = 0;
    g->source = NIL;
    return g;
}

// free all associated memory with G
void freeGraph(Graph* pG){
    for(int i = 0; i <= (*pG)->order; i++){
        freeList(&((*pG)->neighbors[i]));
    }
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->distance);
    free((*pG)->neighbors);
    free(*pG);
    *pG = NULL;
}

/* Access functions */
// return number of vertices (order)
int getOrder(Graph G){
    return G->order;
}

// return number of edges of G
int getSize(Graph G){
    return G->edges;
}

// returns source vertex of G
int getSource(Graph G){
    return G->source;
}

// obtain parent of u
// 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getParent(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling getParent(), u out of range\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

// finds distance from source to u
// 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDist(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling getDist(), u out of range\n");
        exit(EXIT_FAILURE);
    }
    return G->distance[u];
}

// find a shortest path from source to u of graph G
// Pre: getSource()!=NIL and 1 ≤ 𝑢 ≤ getOrder(𝐺)
void getPath(List L, Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling getPath(), u out of range\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G)==NIL){
        fprintf(stderr, "Graph Error: calling getPath(), getSource() is NIL\n");
        exit(EXIT_FAILURE);
    }
    // check if at source vertex
    if(getParent(G, u)==NIL){
        if(u==getSource(G)){
            append(L, u);
        } else {
            append(L, NIL);
        }
        return;
    } else {
        getPath(L, G, getParent(G, u));
        append(L, u);
        return;
    }
}

/* Manipulation procedures */
// clear G
void makeNull(Graph G){
    for(int i = 1; i <= G->order; i++){
        clear(G->neighbors[i]);
    }
    G->edges = 0;
}

// add undirected edge between vertex u and v
void addEdge(Graph G, int u, int v){
    // use temp name for u adjacency list for conciseness
    List temp = G->neighbors[u];

    // check if u's list empty
    if(length(temp) > 0){
        moveFront(temp);
        // add v to u's list
        // ensure list is in increasing order
        while(get(temp) < v && index(temp) < length(temp) - 1){
            // check if v in u's neighbors already
            if(get(temp)==v){
                return;
            }
            moveNext(temp);
        }
        if(get(temp) < v){
            insertAfter(G->neighbors[u], v);
        } else {
            insertBefore(G->neighbors[u], v);
        }
    } else {
        append(temp, v);
    }

    // add v to u's list
    temp = G->neighbors[v];

    if(length(temp) > 0){
        moveFront(temp);
        // add u to v's list
        // ensure list is in increasing order
        while(get(temp) < u && index(temp) < length(temp) - 1){
            // check if u in v's neighbors already
            if(get(temp)==v){
                return;
            }
            moveNext(temp);
        }
        if(get(temp) < u){
            insertAfter(G->neighbors[v], u);
        } else {
            insertBefore(G->neighbors[v], u);
        }
    } else {
        append(temp, u);
    }

    G->edges++;
}

// add directed edge from u to v
void addArc(Graph G, int u, int v){
     // use temp name for u adjacency list for conciseness
    List temp = G->neighbors[u];

    // check if u's list empty
    if(length(temp) > 0){
        moveFront(temp);
        // add v to u's list
        // ensure list is in increasing order
        while(get(temp) < v && index(temp) < length(temp) - 1){
            // check if v already in u's neighbors
            if(get(temp)==v){
                return;
            }
            moveNext(temp);
        }
        if(get(temp) < v){
            insertAfter(G->neighbors[u], v);
        } else {
            insertBefore(G->neighbors[u], v);
        }
    } else {
        append(temp, v);
    }
    G->edges++;
}

// execute breadth first search on G
void BFS(Graph G, int s){
    G->source = s;
    int x, y, i;
    for(x = 1; x <= getOrder(G); x++){
        // exclude source node
        if(x != s){
            G->color[x] = white;
            G->distance[x] = INF;
            G->parent[x] = NIL;
        }
    }
    // check that s has neighbors
    if(length(G->neighbors[s])<1){
        return;
    }
    // discover source, s
    G->color[s] = grey;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    // emulate queue with List ADT
    List Q = newList();
    prepend(Q, s);
    while(length(Q) > 0){
        // dequeue
        x = back(Q);
        deleteBack(Q);
        moveFront(G->neighbors[x]);
        for(i = 0, y = get(G->neighbors[x]);
            i < length(G->neighbors[x]);
            moveNext(G->neighbors[x]), i++){
            y = get(G->neighbors[x]);
            // y is discovered
            if(G->color[y] == white){
                // discover y
                G->color[y] = grey;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                // enqueue
                prepend(Q, y);
            }
        }
        // finish x
        G->color[x] = black;
    }
    freeList(&Q);
}

/* other operations */
// print G
void printGraph(FILE* out, Graph G){
    for(int i = 1; i <= getOrder(G); i++){
        moveFront(G->neighbors[i]);
        fprintf(out, "%d:", i);
        for(int j = 0; j < length(G->neighbors[i]); j++){
            fprintf(out, " %d", get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
        }
        fprintf(out, "\n");
    }
}



