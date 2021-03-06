//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS 101 - PA4                                                                                                                                                                     
//Graph.h                                                                                                                                                                            

#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct GraphObj* Graph;

#include <stdio.h>
#include "List.h"

#define INF -1
#define NIL -2

//Constructors - Destructors                                                                                                                                                         
Graph newGraph(int n);
void freeGraph(Graph* pG);

//Access Functions                                                                                                                                                                   
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

//Manipulationg Procedures                                                                                                                                                           
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

//Other Operations                                                                                                                                                                   
void printGraph(FILE* out, Graph G);

#endif
