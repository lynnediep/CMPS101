//Lynne Diep                                                                                                                                                                         
//lytdiep@ucsc.edu                                                                                                                                                                   
//CMPS101 - PA5                                                                                                                                                                      
//List.c                                                                                                                                                                             

//used same List.c from previous PAs                                                                                                                                                 
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj {
  int data;
  struct NodeObj* next;
  struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;

Node newNode(int data, Node prev, Node next) {
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->prev = prev;
  N->next = next;
  return(N);
}

void freeNode(Node* pN) {
  if(pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

List newList(void){
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = L->cursor = NULL;
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

int length(List L) {
  if(L == NULL) {
    printf("List Error: calling length() on NULL List reference\n");
    exit(1);
  }
  return L->length;
}

int index(List L) {
  if(L == NULL) {
    printf("List Error: calling index() on NULL List reference\n");
    exit(1);
  }
  return L->index;
}

int front(List L) {
  if(L == NULL) {
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
  }
  if(L->length < 1) {
    printf("List Error: calling front() on empty List reference\n");
    exit(1);
  }
  return L->front->data;
}

int back(List L) {
  if(L == NULL) {
    printf("List Error: calling back() on NULL List reference\n");
    exit(1);
  }
  if(L->length < 1) {
    printf("List Error: calling back() on empty List reference\n");
    exit(1);
  }
  return L->back->data;
}

int get(List L) {
  if(L == NULL) {
    printf("List Error: calling get() on NULL List reference\n");
    exit(1);
  }
 if(L->index < 0) {
    printf("List Error: calling get() with undefined index\n");
    exit(1);
  }
  if(L->length < 1) {
    printf("List Error: calling get() on empty List reference\n");
    exit(1);
  }
  return L->cursor->data;
}

int equals(List A, List B) {
  if(A == NULL) {
    printf("List Error: calling equals() on NULL List reference\n");
    exit(1);
  }
  if(B == NULL){
    printf("List Error: calling equals() on NULL\n");
    exit(1);
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

void clear(List L) {
  if(L == NULL) {
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

void moveFront(List L) {
  if(L == NULL) {
    printf("List Error: calling moveFront() on NULL List reference\n");
    exit(1);
  }
  if(L->length > 0) {
    L->cursor = L->front;
     L->index = 0;
  }
}

void moveBack(List L) {
  if(L == NULL) {
    printf("List Error: calling moveBack() on NULL List reference\n");
    exit(1);
  }
  if(L->length > 0) {
    L->cursor = L->back;
    L->index = L->length - 1;
  }
}

void movePrev(List L) {
  if(L == NULL) {
    printf("List Error: calling movePrev() on NULL List reference\n");
    exit(1);
  }
  if(L->cursor != NULL && L->index != 0) {
    L->cursor = L->cursor->prev;
    --L->index;
  }
  else if(L->cursor != NULL && L->index == 0) {
    L->cursor = NULL;
    L->index = -1;
  }
}

void moveNext(List L) {
  if(L == NULL) {
    printf("List Error: calling moveNext() on NULL List reference\n");
    exit(1);
  }
  if(L->cursor != NULL && L->cursor != L->back) {
    L->cursor = L->cursor->next;
    ++L->index;
  }
  else if(L->cursor != NULL && L->cursor == L->back) {
    L->cursor = NULL;
    L->index = -1;
  }
}

void prepend(List L, int data) {
  if(L == NULL) {
    printf("List Error: calling prepend() on NULL List reference\n");
    exit(1);
  }
  Node tmp = newNode(data, NULL, L->front);
  if(L->front == NULL)
    L->back = tmp;
  else
    L->front->prev = tmp;
    L->front = tmp;
  ++L->length;
}

void append(List L, int data) {
  if(L == NULL) {
    printf("List Error: calling append() on NULL List reference\n");
    exit(1);
  }
  Node tmp = newNode(data, L->back, NULL);
  if(L->front == NULL)
    L->front = tmp;
  else
    L->back->next = tmp;
  L->back = tmp;
  ++L->length;
}

void insertBefore(List L, int data) {
  if(L == NULL) {
    printf("List Error: calling insertBefore() on NULL List reference\n");
    exit(1);
  }
  if(L->index < 0) {
    printf("List Error: insertBefore() called with an undefined index on List");
    exit(1);
  }
if(L->length < 1) {
    printf("List Error: insertBefore() called on an empty List");
    exit(1);
  }
  Node tmp = newNode(data, L->cursor->prev, L->cursor);
  if(L->cursor->prev != NULL)
    L->cursor->prev->next = tmp;
  else
    L->front = tmp;
  L->cursor->prev = tmp;
  ++L->length;
}

void insertAfter(List L, int data) {
  if(L == NULL) {
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(1);
  }
  if(L->index < 0) {
    printf("List Error: insertAfter() called with an undefined index on List");
    exit(1);
  }
  if(L->length < 1) {
    printf("List Error: insertAfter() called on an empty List");
    exit(1);
  }
  Node tmp = newNode(data, L->cursor, L->cursor->next);
   if(L->cursor->next != NULL)
    L->cursor->next->prev = tmp;
  else
    L->back = tmp;
  L->cursor->next = tmp;
  ++L->length;
}

void deleteFront(List L) {
  if(L == NULL) {
    printf("List Error: deleteFront() called on NULL List reference\n");
    exit(1);
  }
  if(L->length < 1) {
    printf("List Error: deleteFront() called on an empty List\n");
    exit(1);
  }
  if(L->cursor == L->front) {
    L->cursor = NULL;
    L->index = -1;
  }
  Node tmp = L->front;
  L->front = L->front->next;
  L->front->prev = NULL;
  --L->length;
  freeNode(&tmp);
}

void deleteBack(List L) {
  if(L == NULL) {
    printf("List Error: deleteBack() called on NULL List reference\n");
    exit(1);
  }
  if(L->length < 1) {
    printf("List Error: deleteBack() called on an empty List\n");
    exit(1);
  }
  if(L->back == L->front)
    L->front = NULL;

  Node tmp = L->back;
  if(L->back->prev != NULL)
    L->back = L->back->prev;
  L->back->next = NULL;
  --L->length;
  freeNode(&tmp);
}

void delete(List L) {
  if(L == NULL) {
    printf("List Error: delete() called on NULL List reference\n");
    exit(1);
  }
  if(L->length < 1) {
    printf("List Error: delete() called with an undefined index on List\n");
    exit(1);
  }
  if(L->index < 0) {
    printf("List Error: delete() called on empty List");
    exit(1);
  }
  if(L->cursor == L->back) {
    deleteBack(L);
  } else if(L->cursor == L->front) {
    deleteFront(L);
  } else {
    Node tmp = L->cursor;
    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;
    freeNode(&tmp);
    L->cursor = NULL;
    L->index = -1;
    --L->length;
  }
}

void printList(FILE* out, List L) {
  Node tmp = L->front;
  int i = 0;
  while(tmp != NULL) {
    if(i != 0)
       fprintf(out, " %d", tmp->data);
    else
      fprintf(out, "%d", tmp->data);
    tmp = tmp->next;
    ++i;
  }
}

List copyList(List L) {
  List c = newList();
  Node tmp = L->front;
  while(tmp != NULL) {
    append(c, tmp->data);
    tmp = tmp->next;
  }
  return c;
}
