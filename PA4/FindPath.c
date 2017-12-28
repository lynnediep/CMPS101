//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS101 - PA4                                                                                                                                                                      
//FindPath.c                                                                                                                                                                         


//USED fileIO AS TEMPLATE FROM EXAMPLE                                                                                                                                               
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Graph.h"
#define MAX_LEN 255

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

  int size = 0;
  fgets(line, MAX_LEN, in);
  sscanf(line,"%d", &size);

  Graph G = newGraph(size);
  /* read each line of input file, then count and print tokens */
  while( fgets(line, MAX_LEN, in) != NULL)  {
    int a,b = 0;
    sscanf(line, "%d %d", &a, &b);
    if (a == 0 && b == 0){
      break;
    }
    addEdge(G, a, b);
  }
  printGraph(out, G);

/* read each line of input file, then count and print tokens */
  while( fgets(line, MAX_LEN, in) != NULL)  {
    int a,b = 0;
    sscanf(line, "%d %d", &a, &b);
    if (a == 0 && b == 0){
      break;
    }
    if( count++ != 0){
      fprintf(out, "\n");
    }
    fprintf(out, "\n");
    BFS(G, a);
    int c = getDist(G,b);
    fprintf(out, "Distance from %d to %d is, ", a, b);
    if( c == INF){
      fprintf(out, "infinity\n");
    }
    else{
      fprintf(out, "%d\n", c);
    }
    List X = newList();
    getPath(X, G, b);
    if(front(X) == NIL){
      fprintf(out, "No %d-%d path exists\n", a, b);
    }
    else{
      fprintf(out, "Shortest %d-%d path is: ", a, b);
      printList(out, X);
    }
    freeList(&X);
  }

  fprintf(out, "\n");
  freeGraph(&G);

  //CLOSE FILES                                                                                                                                                                      
  fclose(in);
  fclose(out);
  return(0);
}
