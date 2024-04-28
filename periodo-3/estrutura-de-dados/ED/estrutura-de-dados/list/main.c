#include <stdio.h>
#include "list.h"

void print(void *a) {
    int *value = (int*) a;
   printf("%d ", *value);
}

int cmp(void *a, void *b) {
    int *number1 = (int*) a;
    int *number2 = (int*) b;
    return *number1 - *number2;
}

int main() {
    List *lst = List_alloc();
    int n[] = {4, 2, 9, 1, 8, 3, 7};

    List_insert(lst, &n[0]);
    List_insert(lst, &n[1]);
    List_insert(lst, &n[2]);
    List_insert(lst, &n[3]);
    List_insert(lst, &n[4]);
    List_insert(lst, &n[5]);
    List_insert(lst, &n[6]);

    List_print(lst, print);

    List_remove(lst, &n[3], cmp);
    List_remove(lst, &n[0], cmp);
    List_remove(lst, &n[2], cmp);
    List_remove(lst, &n[1], cmp);

    List_print(lst, print);

    List_remove(lst, &n[6], cmp);
    List_remove(lst, &n[4], cmp);
    List_remove(lst, &n[5], cmp);

    List_insertSorted(lst, &n[0], cmp);
    List_insertSorted(lst, &n[1], cmp);
    List_insertSorted(lst, &n[2], cmp);
    List_insertSorted(lst, &n[3], cmp);
    List_insertSorted(lst, &n[4], cmp);
    List_insertSorted(lst, &n[5], cmp);
    List_insertSorted(lst, &n[6], cmp);

    List_print(lst, print);

    List_free(lst);
    
    return 0;
}