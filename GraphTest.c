/***************************
*  pa2 : GraphTest.c
*  Lucais Sanderson
*  lzsander
***************************/

#include <assert.h>
#include <stdio.h>
#include "Graph.h"

int main(void){
    // test constructors/destructors
    Graph g = newGraph(5);
    assert(g!=NULL);
    assert(g->source==NIL);
    assert(g->order==5);
    assert(g->edges==0);
    freeGraph(&g);
    assert(g==NULL);

    // test access functions
    g = newGraph(6);
    Graph h = newGraph(5);
    assert(getOrder(g)==6);
    assert(getOrder(h)==5);
    assert(getSize(g)==0);
    assert(getSize(h)==0);
    assert(getSource(g)==NIL);
    assert(getSource(h)==NIL);


    // test manipulation functions
    addEdge(g, 1, 3);
    addEdge(g, 1, 2);
    addEdge(g, 3, 4);
    addEdge(g, 2, 4);
    addEdge(g, 2, 5);
    addEdge(g, 2, 6);
    addEdge(g, 4, 5);
    addEdge(g, 5, 6);
    assert(getSize(g)==8);
    assert(getOrder(g)==6);

    printGraph(stdout, g);

    BFS(g, 1);
    assert(getSource(g)==1);
    for(int i = 1; i <= getOrder(g); i++){
        printf("dist(%d)=%d\n", i, getDist(g, i));
    }
    List l = newList();
    for(int i = 1; i <= getOrder(g); i++){
        printf("%d-%d: ", i, getSource(g));
        getPath(l, g, i);
        printList(stdout, l);
        printf("\n");
        clear(l);
    }
    freeList(&l);

    makeNull(g);
    assert(getSize(g)==0);

    freeGraph(&g);
    freeGraph(&h);
    assert(g==NULL);
    assert(h==NULL);
/* 
expected output:

   1: 2 3
2: 1 4 5 6
3: 1 4
4: 2 3 5
5: 2 4 6
6: 2 5
dist(1)=0
dist(2)=1
dist(3)=1
dist(4)=2
dist(5)=2
dist(6)=2
1-1: 1
2-1: 1 2
3-1: 1 3
4-1: 1 2 4
5-1: 1 2 5
6-1: 1 2 6
*/

    // tests from examples!!

   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);


    // check specific test case from grading script
    Graph a = newGraph(100);
    List L = newList();
    List c = newList();
    BFS(a, 42);
    assert(getSource(a)==42);


    // check addArc()
    addArc(a, 64, 4);
    addArc(a, 64, 3);
    addArc(a, 42, 2);
    addArc(a, 2, 64);
    addArc(a, 4, 2);
    addArc(a, 3, 42);

    BFS(a, 99);
    assert(getDist(a, 64)==INF);

    BFS(a, 2);
    append(c, 3);
    append(c, 42);
    append(c, 2);
    append(c, 64);
    append(c, 2);
    getPath(L, a, 99);

    assert(!equals(L,c));

    clear(L);
    clear(c);

    append(c, NIL);
    BFS(a, 99);
    assert(getSource(a)==99);
    getPath(L, a, 2);
    printf("dist(99,2)=%d\n", getDist(a, 2));
    printList(stdout, L);
    printf("\n");
    printList(stdout, c);
    printf("\n");

    assert(equals(c,L));




    return 0;
}


