/***********************
*  pa 2 : FindPath.c
*  Lucais Sanderson
*  lzsander
************************/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char** argv){
    FILE* in;
    FILE* out;
    int size, v1, v2; // intermittent vertices 

    // check number of args
    if(argc != 3){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if(in == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(out == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // get first line for number of vertices
    if(fscanf(in, "%d\n", &size) != 1){
        fprintf(stderr, "Error reading graph size (first line not formatted correctly)\n");
        exit(EXIT_FAILURE);
    }

    Graph G = newGraph(size);
    List L = newList();

    // add vertex entries
    while(fscanf(in, "%d %d\n", &v1, &v2)!=EOF){
        if(!(v1 && v2)) break;
        addEdge(G, v1, v2);
    }

    // print graph
    printGraph(out, G);
    fprintf(out, "\n");

    // execute BFS and print paths
    while(fscanf(in, "%d %d\n", &v1, &v2)!=EOF){
        if(!(v1 && v2)) break;
        BFS(G, v1);
        getPath(L, G, v2);
        if(getDist(G, v2) == INF){
            fprintf(out, "The distance from %d to %d is infinity\n", getSource(G), v2);
            fprintf(out, "No %d-%d path exists", getSource(G), v2);
        } else {
            fprintf(out, "The distance from %d to %d is %d\n", getSource(G), v2, getDist(G, v2));
            fprintf(out, "A shortest %d-%d path is:", getSource(G), v2);
            printList(out, L);
        }
        fprintf(out, "\n\n");
        clear(L);
    }

    freeGraph(&G);
    freeList(&L);

    fclose(in);
    fclose(out);

    return 0;
}
