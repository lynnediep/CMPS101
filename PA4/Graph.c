//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS101 - PA4                                                                                                                                                                      
//Graph.c                                                                                                                                                                            

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

struct GraphObj{
  List *adj; //array of Lists whose ith element contains the neighbors of vertex i                                                                                                   
  int *color; //array of ints whose ith element is the color of vertex i                                                                                                             
  int *parent; //array of ints whose ith element is the parent of vertex i                                                                                                           
  int *distance; //array of ints whose ith element is the distance of vertex i                                                                                                       
  int order;
  int size;
  int source;
};

Graph newGraph(int n){ //returns a Graph pointing to a newly created GraphObj                                                                                                        
  Graph G = malloc(sizeof(struct GraphObj));
  G->adj = calloc(n+1,sizeof(List));
  G->color = calloc(n+1,sizeof(int));
  G->parent = calloc(n+1,sizeof(int));
  G->distance = calloc(n+1,sizeof(int));
  G->order = n;
  G->size = 0;
  G->source = NIL;

  for(int i = 0; i < (n+1); i++){
    G->adj[i] = newList();
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->distance[i] = INF;
  }
  return G;
}

//frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL.                                                                                          
void freeGraph(Graph* pG){
  Graph used = *pG;
  for(int i = 0; i < (used->order + 1); i++){
    freeList(&(used->adj[i]));
  }
  free(used->adj);
  free(used->color);
  free(used->parent);
  free(used->distance);
  free(*pG);
   *pG = NULL;
}

int getOrder(Graph G){ //return corresponding field values                                                                                                                           
  return G->order;
}

int getSize(Graph G){ //return crresponding field values                                                                                                                             
  return G->size;
}

int getSource(Graph G){ //returns the source vertex most recently used in function BFS()                                                                                             
  return G->source;
}

int getParent(Graph G, int u){//will return the parent of vertex u in the BreadthFirst tree                                                                                          
  //precondition 1 <= u <= getOrder()                                                                                                                                                
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

int getDist(Graph G, int u){//returns the distance from the most recent BFS source to vertex u                                                                                       
  //precondition 1 <= u <= getOrder()                                                                                                                                                
  if(1 > u){
    printf("Graph Error: getDist() out of bounds\n");
    exit(1);
  }
  if(u > getOrder(G)){
    printf("Graph Error: getDist() out of bounds\n");
    exit(1);
  }
  return G->distance[u];
}

void getPath(List L, Graph G, int u){//appends to the List L the vertices of a shortest path in G from source to u                                                                   
  //precondition 1 <= u <= getOrder()                                                                                                                                                
  if(1 > u){
    printf("Graph Error: getDist() out of bounds\n");
    exit(1);
  }
  if(u > getOrder(G)){
    printf("Graph Error: getDist() out of bounds\n");
    exit(1);
  }
  int sour = G->source;
  if (u == sour){//prepend if true                                                                                                                                                   
    prepend(L,sour);
  }
  else if(G->parent[u] == NIL){//append if true                                                                                                                                      
    append(L,NIL);
  }
  else{
    prepend(L,u);
    getPath(L, G, G->parent[u]);
  }
}

//Manipulation Procedures                                                                                                                                                            
void makeNull(Graph G){//deletes all edges of G, restoring it to its original (no edge) state                                                                                        
  for(int i = 0; i < (G->order + 1); i++){
    clear(G->adj[i]);
  }
}

void addEdge(Graph G, int u, int v){//inserts a new edge joining u to v, i.e. u is added to the adjacency      
 // two int arguments must lie in the range 1 to getOrder(G)                                                                                                                        
  // 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)                                                                                                                                    
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

void addArc(Graph G, int u, int v){//inserts a new directed edge from u to v                                                                                                         
  // two int arguments must lie in the range 1 to getOrder(G)                                                                                                                        
  // 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)                                                                                                                                    
  if (1 > u || u > getOrder(G)){
    printf("Graph Error: addEdge() with vertices out of bound\n");
    exit(1);
  }
  if (1 > v || v > getOrder(G)){
    printf("Graph Error: addEdge() with vertices out of bound\n");
    exit(1);
  }
  List S = G->adj[u];
  moveFront(S);
  while(index(S) > -1 && v > get(S)){
    moveNext(S);
  }
  if(index(S) == -1){ //append if true                                                                                                                                               
    append(S,v);
  }
  else{//if index(S) != -1                                                                                                                                                           
    insertBefore(S,v);
  }
  G->size++;
}

void BFS(Graph G, int s){//runs the BFS algorithm on the Graph G with source s                                                                                                       
  //used notes of BFS algorithm from lecture as template                                                                                                                             
  for(int i = 0; i < (G->order + 1); i++){
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->distance[i] = INF;
  }
  G->source = s;
  G->color[s] = GRAY;
  G->distance[s] = 0;
  List Q = newList();
  prepend(Q,s);
  while(length(Q) > 0){
    int x = back(Q);
    delete(Q);
    List adj = G->adj[x];
    moveFront(adj);
    while(index(adj) > -1){
      int y = get(adj);
      if(G->color[y] == WHITE){
        G->color[y] = GRAY;
        G->parent[y] = x;
        G->distance[y] = G->distance[x] + 1;
        prepend(Q,y);
      }
      moveNext(adj);
    }
  }
  freeList(&Q);
}

//Other Operations                                                                                                                                                                   
void printGraph(FILE* out, Graph G){//prints the adjacency list representation of G                                                                                                  
  //Queue template taken from notes                                                                                                                                                  
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
