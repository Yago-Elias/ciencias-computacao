#include <stdlib.h>
#include <stdio.h>
#include "List.h"

typedef struct Node Node;

struct Node {
  int value;
  Node *next;
};

struct List {
  int length;
  Node *first;
};

List *List_alloc() {
  List *l = malloc(sizeof(List));
  if (l) {
    l->length = 0;
    l->first = NULL;
  }
  return l;
}

void List_free(List *l) {
  Node *n = NULL;
  Node *next = NULL;
  
  if (l) {
    n = l->first;
    
    while (n) {
      next = n->next;
      free(n);
      n = next;
    }
    
    free(l);
  }
}

void List_insert(List *l, int value) {
  Node *new = NULL;
  
  if (l) {
    new = malloc(sizeof(Node));
    new->value = value;
    new->next = NULL;
    
    if (l->length > 0)
      new->next = l->first;

    l->first = new;
    l->length++;
  }
}

void List_insertSorted(List *l, int value) {
  Node *new = NULL, *ant = NULL, *n = NULL;
  
  if (l) {
    new = malloc(sizeof(Node));
    new->value = value;
    new->next = NULL;
    
    if (l->length == 0) {
      l->first = new;
    }
    else {
      n = l->first;
      while (n) {
        if (new->value < n->value)
          break;
        ant = n;
        n = n->next;
      }
      
      if (ant)
        ant->next = new;
      else
        l->first = new;
        
      new->next = n;
    }
      
    l->length++;
  }
}

int List_remove(List *l, int value) {
  Node *n = NULL;
  Node *ant = NULL;
  int aux = 0;
  
  if (l) {
    n = l->first;
    
    while (n) {
      if (n->value == value) {
        
        if (ant == NULL)
          l->first = n->next;
        else
          ant->next = n->next;          
        
        aux = n->value;
        free(n);
        l->length--;
        
        break;
      }
      
      ant = n;
      n = n->next;
    }
  }
  
  return aux;
}

int List_getLength(List *l) {
  if (l)
    return l->length;
  
  return 0;
}

void List_print(List *l) {
  Node *n = NULL;
  
  if (l) {
    n = l->first;
    
    printf("List(%d): ", l->length);
    
    while (n) {
      printf("%d ", n->value);
      n = n->next;
    }
    
    printf("\n");
  }
}


