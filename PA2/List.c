//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPE 101 - PA2                                                                                                                                                                     
//List.c                                                                                                                                                                             

//FIXED insertAfter() and insertBefore()                                                                                                                                             
//Misuse of "{}" caused error                                                                                                                                                        
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

typedef struct NodeObj{
  int data;
  struct NodeObj* previous;
  struct NodeObj* next;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;

Node newNode(int data, Node previous, Node next){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->previous = previous;
  N->next = next;
  return(N);
}

void freeNode(Node* pN){
  if( pN!=NULL && *pN!=NULL ){
    free(*pN);
    *pN = NULL;
  }
}

List newList(void){
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = NULL;
  L->length = 0;
  L->index = -1;
  return(L);
}

void freeList(List* pL) {
  if(pL != NULL && *pL != NULL) {
     Node tmp = (*pL)->front;
    while(tmp != NULL) {
      Node cur = tmp;
      tmp = tmp->next;
      free(cur);
    }
    free(*pL);
    *pL = NULL;
  }
}

int length(List L){
  if(L == NULL) {
    printf("List Error: calling length() on NULL List reference\n");
    exit(1);
  }
  return(L->length);
}

int index(List L){
  if(L == NULL){
    printf("List Error: calling index() on NULL List reference\n");
    exit(1);
  }
  return(L->index);
}

int front(List L){
  if(L == NULL){
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
  }
  if((L->length)<=0){
    printf("List Error: calling front() called on empty list\n");
    exit(1);
  }
  return(L->front->data);
}

int back(List L){
  if(L == NULL){
    printf("List Error: calling back() on NULL List reference\n");
    exit(1);
  }
  if((L->length)<=0){
    printf("List Error: back() called on empty list\n");
    exit(1);
  }
  return(L->back->data);
}

int get(List L){
  if(L == NULL){
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
  }
  if((L->length)<=0){
    printf("List Error: get() called on empty list\n");
    exit(1);
  }
  if((L->index)<0){
    printf("List Error: get() called on an unassigned index\n");
    exit(1);
  }
  return(L->cursor->data);
}

int equals(List A, List B){
  int flag = 1;     //return true                                                                                                                                                    
  Node n = NULL;
  Node m = NULL;

  if(A==NULL||B==NULL){
    printf("List Error: calling equals() on NULL list reference\n");
    exit(1);
  }

  if(A->length != B->length) {
    return 0;
  }
  Node cfront = B->front;
  Node tmp = A->front;
  while(cfront->next != NULL && tmp->next != NULL) {
    if(cfront->data != tmp->data)
      return 0;
    cfront = cfront->next;
    tmp = tmp->next;
  }
  return 1;
}

void clear(List L){
  if (L == NULL){
    printf("List Error: calling clear() on NULL List reference\n");
    exit(1);
  }
  Node tmp = L->front;
  while(tmp != NULL) {
    Node cur = tmp;
    tmp = tmp->next;
    free(cur);
  }
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->index = -1;
}

void moveFront(List L){
  if (L == NULL){
    printf("List Error: calling moveFront() on NULL List reference\n");
    exit(1);
  }
  if((L->length)>0){
    (L->cursor) = (L->front);
    (L->index) = 0;
  }
}

void moveBack(List L){
  if (L == NULL){
    printf("List Error: calling moveBack() on NULL List reference\n");
    exit(1);
  }
  if((L->length)>0){
    (L->cursor) = (L->back);
    (L->index) = ((L->length)-1);
  }
}

void movePrev(List L){
  if (L == NULL){
    printf("List Error: calling movePrev() on NULL List reference\n");
    exit(1);
  }
  if((L->cursor)!=NULL && (L->index)!=0){
    (L->cursor) = (L->cursor->previous);
    (L->index) = ((L->index)-1);
  }
  else if((L->cursor)!=NULL && (L->index)==0){
    (L->cursor) = NULL;
    (L->index) = -1;
  }
}

void moveNext(List L){
  if (L == NULL){
    printf("List Error: calling moveNext() on NULL List reference\n");
    exit(1);
  }
  if((L->cursor)!=NULL && (L->index) != ((L->length)-1)){
      (L->cursor) = (L->cursor->next);
      (L->index) = ((L->index)+1);
  }
  else if((L->cursor)!=NULL && (L->index)==((L->length)-1)){
      (L->cursor) = NULL;
      (L->index) = -1;
  }
}

void prepend(List L, int data){
  if (L == NULL){
    printf("List Error: calling prepend() on NULL List reference\n");
    exit(1);
  }
  Node tmp = newNode(data, NULL, L->front);
  if(L->front == NULL)
    L->back = tmp;
  else
    L->front->previous = tmp;
  L->front = tmp;
  ++L->length;
}

void append(List L, int data){
  if (L == NULL){
    printf("List Error: calling append() on NULL List reference\n");
    exit(1);
  }
  Node newElement = newNode(data,L->back, NULL);
  if(L->length <= 0){
    L->back = L->front = newElement;
  }
  else{
    L->back->next = newElement;
    newElement->previous = L->back;
    L->back = newElement;
  }
  ++L->length;
}

void insertBefore(List L, int data){
  if (L == NULL){
    printf("List Error: calling insertBefore() on NULL List reference\n");
    exit(1);
  }
  if(L->length <= 0){
    printf("List Error: insertBefore called on empty list\n");
    exit(1);
  }
  if(L->index < 0){
    printf("List Error: insertBefore called on undefined index\n");
    exit(1);
  }
  Node temp = newNode(data,L->cursor->previous, L->cursor);
  if(L->cursor->previous != NULL)
    L->cursor->previous->next = temp;
  else
    L->front = temp;
    L->cursor->previous = temp;
   ++L->length;
}

void insertAfter(List L, int data){
  if (L == NULL){
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(1);
    }
  if(L->index < 0){
    printf("List Error: insertAfter() called on undefined index\n");
    exit(1);
  }
  if(L->length <= 0){
    printf("List Error: insertAfter() called on an empty list\n");
    exit(1);
  }
  Node tmp = newNode(data, L->cursor, L->cursor->next);
  if(L->cursor->next != NULL)
    L->cursor->next->previous = tmp;
  else
    L->back = tmp;
    L->cursor->next = tmp;
    ++L->length;
}

void deleteFront(List L){
  if (L == NULL){
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(1);
  }
  if(L->length <= 0){
    printf("List Error: deleteFront() called on empty list\n");
    exit(1);
  }
   else{
    Node temp = L->front;
    L->front = L->front->next;
    L->front->previous = NULL;
    --L->length;
    freeNode(&temp);
  }
}

void deleteBack(List L){
  if (L == NULL){
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(1);
  }
  if(L->length <= 0){
    printf("List Error: deleteBack() called on empty list\n");
    exit(1);
  }
  if(L->cursor == L->front) {
    L->cursor = NULL;
    L->index = -1;
  }
  else{
    Node temp = L->back;
    L->back = L->back->previous;
    L->back->next = NULL;
    --L->length;
    freeNode(&temp);
  }
}

void delete(List L){
  if (L == NULL){
    printf("List Error: calling delete() on NULL List reference\n");
    exit(1);
  }
  if(L->length <= 0){
    printf("List Error: delete() called on empty list\n");
    exit(1);
  }
  if(L->index <0){
    printf("List Error: delete() called on undefined index\n");
    exit(1);
  }
  else{
    Node temp = L->cursor;
    L->cursor->previous->next = L->cursor->next;
    L->cursor->next->previous = L->cursor->previous;
    L->cursor = NULL;
    L->index = -1;
    --L->length;
    freeNode(&temp);
  }
}

void printList(FILE* out, List L){
  if (L == NULL){
    printf("List Error: calling printList() on NULL List reference\n");
    exit(1);
  }
  Node tmp = L->front;
  while(tmp != NULL) {
    printf("%d ", tmp->data);
    tmp = tmp->next;
  }
}

List copyList(List L){
  if (L == NULL){
    printf("List Error: calling copyList() on NULL List reference\n");
    exit(1);
  }
  List N = newList();
  Node temp = L->front;
  while(temp !=NULL){
    append(N, temp->data);
    temp = temp->next;
  }
  return(N);
}

