#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct Queue {
    int size;
    int begin;
    int end;
    void **elements;
};

Queue *Queue_alloc(int size) {
    Queue *q = malloc(sizeof(Queue));

    if (q) {
        q->size = size;
        q->begin = -1;
        q->end = -1;
        q->elements = calloc(size, sizeof(void*));
    }

    return q;
}

void Queue_free(Queue *q) {
    if (q) {
        free(q->elements);
        free(q);
    }
}

int Queue_isEmpty(Queue *q) {
    if (q) {
        return q->begin == -1 && q->end == -1;
    }

    return 1;
}

int Queue_nextIndex(Queue *q, int index) {
    if (q && index >= 0)
        return (index + 1) % q->size;
    
    return 0;
}

int Queue_isFull(Queue *q) {
    if (q) {
        return Queue_nextIndex(q, q->end) == q->begin;
    }

    return 0;
}

void Queue_push(Queue *q, void *item) {
    if (q) {
        if (!Queue_isFull(q)) {
            if (Queue_isEmpty(q))
                q->begin = 0;

            q->end = Queue_nextIndex(q, q->end);
            q->elements[q->end] = item;
        }
    }
}

void *Queue_pop(Queue *q) {
    void *item = NULL;

    if (q) {
        if (!Queue_isEmpty(q)) {
            item = q->elements[q->begin];

            if (q->begin == q->end) {
                q->begin = -1;
                q->end = -1;
            }
            else
                q->begin = Queue_nextIndex(q, q->begin);
        }
    }

    return item;
}

void *Queue_begin(Queue *q) {
    if (q) {
        if (!Queue_isEmpty(q))
            return q->elements[q->begin];
    }

    return NULL;
}

void *Queue_end(Queue *q) {
    if (q) {
        if (!Queue_isEmpty(q))
            return q->elements[q->end];
    }

    return NULL;
}

void Queue_print(Queue *q, void (*print)(void*)) {
    int i;

    if (q) {
        printf("Queue: ");

        if (!Queue_isEmpty(q)) {
            for (i = q->begin; i != q->end; i = Queue_nextIndex(q, i)) {
                printf("[");
                print(q->elements[i]);
                printf("]->");
            }
            
            printf("[");
            print(q->elements[q->end]);
            printf("]");
        }

        printf("\n");
    }
}

