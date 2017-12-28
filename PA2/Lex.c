//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS 101 - PA2                                                                                                                                                                     
//Lex.c                                                                                                                                                                              

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){

  int n, count=0;
  FILE *in, *out;
  char line[MAX_LEN];
  char tokenlist[MAX_LEN];
  char* token;

  if( argc != 3 ){ //check that there are not 3 command line arguments                                                                                                               
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  in = fopen(argv[1], "r");//open files for reading and writing                                                                                                                      
  out = fopen(argv[2], "w");
  if( in==NULL ){
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  if( out==NULL ){
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  while( fgets(line, MAX_LEN, in) != NULL)  {//count number of lines                                                                                                                 
    count++;
  }

  rewind(in);//back to front of list                                                                                                                                                 

  char word[count - 1][MAX_LEN]; //copy file into string array                                                                                                                       
  n = -1;

  while(fgets(line, MAX_LEN, in) != NULL) {
    strcpy(word[++n], line);
  }

  List list = newList();

  append(list,0);

  for(int j = 1; j<count; j++){ //insertion sort                                                                                                                                     
    char*temp = word[j];
    int i = j-1;
    moveBack(list);

    while(i>=0 && strcmp(temp,word[get(list)])<=0){
      i--;
      movePrev(list);
    }
    if(index(list) >=0){
      insertAfter(list,j);
    }
    else{
      prepend(list,j);
    }
  }

  moveFront(list);

  while(index(list)>=0){ //print out sorted list                                                                                                                                     
    fprintf(out, "%s", word[get(list)],"\n");
    moveNext(list);
  }

  fclose(in); //close in file                                                                                                                                                        
  fclose(out);//close out file                                                                                                                                                       
  freeList(&list);
  return(0);
}
