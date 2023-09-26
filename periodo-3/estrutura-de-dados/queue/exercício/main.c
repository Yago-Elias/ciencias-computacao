#include <stdio.h>
#include "../queue.h"

void printInt(void *a) {
    int *n = (int*)a;
    printf("%d", *n);
}

int main() {
    int n[] = {4, 2, 9, 1, 8, 3, 7};
    Queue *q = Queue_alloc(5);
    int *p = NULL;

    Queue_push(q, &n[0]);
    Queue_push(q, &n[1]);
    Queue_push(q, &n[2]);
    Queue_push(q, &n[3]);
    Queue_push(q, &n[4]);
    Queue_push(q, &n[5]);
    Queue_push(q, &n[6]);
    
    p = (int*) Queue_begin(q);
    printf("begin: %d\n", *p);
    p = (int*) Queue_end(q);
    printf("end: %d\n", *p);

    Queue_print(q, printInt);

    p = (int*) Queue_pop(q);
    printf("%d\n", *p);

    Queue_print(q, printInt);

    p = (int*) Queue_pop(q);
    printf("%d\n", *p);
    
    Queue_print(q, printInt);

    Queue_free(q);
    return 0;
}