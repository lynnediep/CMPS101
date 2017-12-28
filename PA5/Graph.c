//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS101 - PA5                                                                                                                                                                      
//Graph.c                                                                                                                                                                            

//used Graph.c from PA4                                                                                                                                                              
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

struct GraphObj{
  List *adj;
  int *color;
  int *parent;
  int *discover;
  int *finish;
  int order;
  int size;
};

//return referecnce to new graph object                                                                                                                                              
//n vertices, no edges                                                                                                                                                               
Graph newGraph(int n){
  Graph G = malloc(sizeof(struct GraphObj));
  G->adj = calloc(n+1,sizeof(List));
  G->color = calloc(n+1,sizeof(int));
  G->parent = calloc(n+1,sizeof(int));
  G->discover = calloc(n+1,sizeof(int));
  G->finish = calloc(n+1,sizeof(int));
  G->order = n;
  G->size = 0;

  for(int i = 0; i < (n+1); i++){
    G->adj[i] = newList();
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }
  return G;
}

//frees all heap memory                                                                                                                                                              
//sets Graph arguments to NULL                                                                                                                                                       
void freeGraph(Graph* pG){
  Graph used = *pG;
  for(int i = 0; i < (used->order + 1); i++){
    freeList(&(used->adj[i]));
  }
 free(used->adj);
  free(used->color);
  free(used->parent);
  free(used->discover);
  free(used->finish);
  free(*pG);
  *pG = NULL;
}

int getOrder(Graph G){
  return G->order;
}

int getSize(Graph G){
  return G->size;
}

int getParent(Graph G, int u){
  if(1 > u){
    printf("Graph Error: getParent() out of bounds\n");
    exit(1);
  }
  if(u > getOrder(G)){
    printf("Graph Error: getParent() out of bounds\n");
    exit(1);
  }
  return G->parent[u];
}

int getDiscover(Graph G, int u){ /* Pre: 1<=u<=n=getOrder(G) */
  if(1 > u){
    printf("Graph Error: getDiscover() out of bounds\n");
    exit(1);
  }
  if(u > getOrder(G)){
    printf("Graph Error: getDiscover() out of bounds\n");
    exit(1);
  }
  return G->discover[u];
}

int getFinish(Graph G, int u){/* Pre: 1<=u<=n=getOrder(G) */
  if(1 > u){
    printf("Graph Error: getFinish() out of bounds\n");
    exit(1);
  }
  if(u > getOrder(G)){
    printf("Graph Error: getFinish() out of bounds\n");
    exit(1);
  }
  return G->finish[u];
}

//Manipulation Process         
//same as pa4                                                                                                                                                                        
void addArc(Graph G, int u, int v){
  if (1 > u || u > getOrder(G)){
    printf("Graph Error: addArc() with vertices out of bound\n");
    exit(1);
  }
  if (1 > v || v > getOrder(G)){
    printf("Graph Error: addArc() with vertices out of bound\n");
    exit(1);
  }
  List S = G->adj[u];
  moveFront(S);
  while(index(S) > -1 && v > get(S)){
    moveNext(S);
  }
  if(index(S) == -1) //append if true                                                                                                                                                
    append(S,v);
  else//if index(S) != -1                                                                                                                                                            
    insertBefore(S,v);
  G->size++;
}

//same as pa4                                                                                                                                                                        
void addEdge(Graph G, int u, int v){
  if (1 > u || u > getOrder(G)){
    printf("Graph Error: addEdge() with vertices out of bound\n");
    exit(1);
 }
  if (1 > v || v > getOrder(G)){
    printf("Graph Error: addEdge() with vertices out of bound\n");
    exit(1);
  }
  addArc(G,u,v);
  addArc(G,v,u);
  G->size--;
}
//recursice algorithm Vist()                                                                                                                                                         
void Visit(Graph G, List S, int u, int *time){
  G->color[u] = GRAY;
  G->discover[u] = ++*time;
  moveFront(G->adj[u]);
  while(index(G->adj[u]) >= 0){
    int v = get(G->adj[u]);
    if(G->color[v] == WHITE){
      G->parent[v] = u;
      Visit(G,S,v,time);
    }
    moveNext(G->adj[u]);
  }
  G->color[u] = BLACK;
  G->finish[u] = ++*time;
  prepend(S,u);
}

//used DFS pseudocode as template                                                                                                                                                    
void DFS(Graph G, List S){
  if(length(S) != getOrder(G)){
    printf("Graph Error: DFS() without mathcing sizes\n");
    exit(1);
  }
  for(int i = 1; i<=getOrder(G); i++){
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }
  int time = 0;
  moveFront(S);
  while(index(S) >= 0) {
    int u = get(S);
    if(G->color[u] == WHITE){
      Visit(G,S,u,&time);
    }
    moveNext(S);
  }
  for(int size = length(S)/2; size > 0; size--){
    deleteBack(S);
  }
}

//OTHER FUNCTIONS         
Graph transpose(Graph G){
  Graph A = newGraph(getOrder(G));
  for(int i = 1; i <= getOrder(G); i++){
    moveFront(G->adj[i]);
    while(index(G->adj[i]) >= 0){
        addArc(A, get(G->adj[i]), i);
        moveNext(G->adj[i]);
      }
  }
  return A;
}

Graph copyGraph(Graph G){
  Graph B = newGraph(getOrder(G));
  for(int i = 1; i <= getOrder(G); i++){
    moveFront(G->adj[i]);
    while(index(G->adj[i]) >= 0){
      addArc(B,i, get(G->adj[i]));
      moveNext(G->adj[i]);
    }
  }
  return B;
}

void printGraph(FILE* out , Graph G){
  if (out == NULL){
    printf("Graph Error: printGraph() called on NULL\n");
    exit(1);
  }
  if(G == NULL){
    printf("Graph Error: printGraph() called on NULL\n");
    exit(1);
  }
  for(int i = 1; i <= getOrder(G); i++){
    fprintf(out, "%d: ", i);
    printList(out, G->adj[i]);
    fprintf(out, "\n");
  }
}
