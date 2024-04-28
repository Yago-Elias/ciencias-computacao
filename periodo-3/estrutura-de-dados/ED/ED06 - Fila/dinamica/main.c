#include <stdio.h>
#include "queue.h"

int main() {
    Queue *q = Queue_alloc(10);

    Queue_push(q, 4);
    Queue_push(q, 1);
    Queue_push(q, 8);
    Queue_push(q, 2);
    Queue_push(q, 9);
    Queue_push(q, 0);

    Queue_print(q);

    printf("%d\n", Queue_pop(q));
    printf("%d\n", Queue_pop(q));
    printf("%d\n", Queue_pop(q));

    Queue_print(q);

    Queue_free(q);

    return 0;
}
