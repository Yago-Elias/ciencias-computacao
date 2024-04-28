#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
struct Queue {
    int size;
    int begin;
    int end;
    int *elements;
};

Queue *Queue_alloc(int size) {
    Queue *q = malloc(sizeof(Queue));
    if (q) {
	q->size = size;
	q->begin = -1;
	q->end = -1;

	q->elements = calloc(size, sizeof(int));
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
}

int Queue_next(Queue *q, int index) {
    if (q  && index >= 0)
	return (index + 1) % q->size;
    return 0;
}

int Queue_isFull(Queue *q) {
    if (q)
	return Queue_next(q, q->end) == q->begin;
    return 0;
}

void Queue_push(Queue *q, int item) {
    if (q)
	if (!Queue_isFull(q)) {
	    if (Queue_isEmpty(q))
		q->begin = 0;
	    q->end = Queue_next(q, q->end);

	    q->elements[q->end] = item;
	}
}

int Queue_pop(Queue *q) {
    int item = 0;

    if (q) {
	if (!Queue_isEmpty(q)) {
	    item = q->elements[q->begin];

	    if (q->begin == q->end) {
		q->begin = -1;
		q->end = -1;
	    }
	    else
		q->begin = Queue_next(q, q->begin);
	    q->size--;
	}
    }
    return item;
}

int Queue_begin(Queue *q) {
    if (q)
	if (!Queue_isEmpty(q))
	    return q->elements[q->begin];
    return 0;
}

int Queue_end(Queue *q) {
    if (q)
	if (!Queue_isEmpty(q))
	    return q->elements[q->end];
    return 0;
}

void Queue_print(Queue *q) {
    int i;

    if (q) {
	if (!Queue_isEmpty(q)) {
	    printf("Queue:\n");
	    for (i = q->begin; i != q->end; i = Queue_next(q, i))
		printf("[%d]->", q->elements[i]);
	    printf("[%d]\n", q->elements[q->end]);
	}
    }
}
