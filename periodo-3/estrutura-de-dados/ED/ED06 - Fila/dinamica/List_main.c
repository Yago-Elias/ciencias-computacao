#include <stdio.h>
#include "List.h"

int main() {
  List *l = List_alloc();
  
  List_insertSorted(l, 4);
  List_print(l);
  List_insertSorted(l, 8);
  List_print(l);
  List_insertSorted(l, 2);
  List_print(l);
  List_insertSorted(l, 6);
  List_print(l);
  
  printf("%d\n", List_remove(l , 8));
  List_print(l);
  printf("%d\n", List_remove(l , 4));
  List_print(l);
  
  List_free(l);
  
  return 0;
}
