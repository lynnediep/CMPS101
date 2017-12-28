//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS101 - PA5                                                                                                                                                                      
//FindComponents.c                                                                                                                                                                   

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Graph.h"
#define MAX_LEN 255

//USE FileIO.c as template                                                                                                                                                           

int main(int argc, char * argv[]){

  int n, count=0;
  FILE *in, *out;
  char line[MAX_LEN];

  // check command line for correct number of arguments                                                                                                                              
  if( argc != 3 ){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  // open files for reading and writing                                                                                                                                              
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  if( in==NULL ){
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  if( out==NULL ){
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  fgets(line, MAX_LEN, in);
  int size = 0;
  sscanf(line, "%d", &size);
  List S = newList();
  for(int x = 1; x <= size; x++)
    append(S, x);


  //Assemble a graph object G using newGraph() and addArc().                                                                                                                         
  Graph G = newGraph(size);
  while(fgets(line, MAX_LEN, in) != NULL){
    int a = 0;
    int b = 0;
    sscanf(line, "%d %d", &a, &b);
    if(a == 0 && b == 0)
      break;
    addArc(G,a,b);
  }

  //Run DFS, processing the vertices in the second call by decreasing                                                                                                                
  //finish times from the first call                                                                                                                                                 
  DFS(G,S);
  Graph T = transpose(G);
  int scc = 0; //scc - strong-connected-components                                                                                                                                   
  DFS(T,S);
  moveFront(S);
  while(index(S) >= 0){ //Determine the strong components of G                                                                                                                       
    if(getParent(T, get(S)) == NIL)
      scc++;
    moveNext(S);
  }

  List listScc[scc];
  for(int i = 0; i<scc; i++){
    listScc[i] = newList();
  }

  moveFront(S);
  int l = scc;
  while(index(S) >= 0){
    if(getParent(T,get(S)) == NIL)
      l--;
    if(l == scc)
       break;
    append(listScc[l], get(S));
    moveNext(S);
  }

  //Print out                                                                                                                                                                        
  //Print the strong components of G to the output file in topologically sorted order                                                                                                
  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);
  fprintf(out, "\nG contains %d strongly connected components:", scc);
  for(int m = 0; m < scc; m++){
    fprintf(out, "\nComponent %d: ", (m+1));
    printList(out, listScc[m]);
    freeList(&(listScc[m]));
  }

  fprintf(out, "\n");
  freeGraph(&G);
  freeGraph(&T);
  freeList(&S);

  //Close files                                                                                                                                                                      
  fclose(in);
  fclose(out);
  return(0);
}
