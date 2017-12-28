//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS101 - PA4                                                                                                                                                                      
//GraphTest.c                                                                                                                                                                        



//USED GRAPHCLIENT FROM EXAMPLE                                                                                                                                                      
//OWN TESTING METHODS AT BOTTOM                                                                                                                                                      
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
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


  //Own Testing                                                                                                                                                                      
  Graph A = newGraph(150);
  for(int i = 1; i < 150; i++){
    BFS(A,i);
    for(int j = 1; j < 150; j++){
      int k = getDist(A,j);
      if( k != INF){
        printf("Distance %d-%d: %d\n", i, j, k);
      }
    }
  }

  BFS(A, 30);
  List D = newList();
  getPath(D,A,10);
  printf("Print path from 30 to 10: ");
  printList(stdout, D);
  printf("\n");

  BFS(A,20);
  List B = newList();
  getPath(B,A, 130);
  printf("Print path from 20 to 130: ");
  printList(stdout, B);
  printf("\n");

  freeList(&D);
  freeList(&B);

  return(0);
}
