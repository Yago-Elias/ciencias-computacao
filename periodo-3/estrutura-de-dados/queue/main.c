#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int size;
    int begin;
    int end;
    void **elements;
} Queue;

void printInt(void *a) {
  int *n = (int*)a;
  printf("%d", *n);
}


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
    if(q){
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

int Queue_next(Queue *q, int index) {
    if (q && index >= 0)
        return (index + 1) % q->size;
    
    return 0;
}

int Queue_isFull(Queue *q) {
   if (q) 
       return Queue_next(q, q->end) == q->begin; 
   
   return 0;
}

void Queue_push(Queue *q, void *el) {
    if (q) {
        if (!Queue_isFull(q)) {
            if (Queue_isEmpty(q))
                q->begin = 0;
            
            q->end = Queue_next(q, q->end);
            
            q->elements[q->end] = el;
        }
    }
}

void Queue_print(Queue *q, void (*print)(void*)) {
    int i;
    if (q) {
        printf("Queue: ");
        
        if (!Queue_isEmpty(q)) {
            for (i=q->begin; i != q->end; i = Queue_next(q, i)) {
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

void *Queue_pop(Queue *q) {
    void *el = NULL;
    
    if (q) {
        if (!Queue_isEmpty(q)) {
            el = q->elements[q->begin];
            
            if (q->begin == q->end) {
                q->begin = -1;
                q->end = -1;
            }
            else
                q->begin = Queue_next(q, q->begin); 
        }
    }
    
    return el;
}

void *Queue_begin(Queue *q) {
    if (q){
        if (!Queue_isEmpty(q))
            return q->elements[q->begin];
    }
    return NULL;
}

void *Queue_end(Queue *q) {
    if (q){
        if (!Queue_isEmpty(q))
            return q->elements[q->end];
    }
    return NULL;
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
    printf("begin %d\n", *p);
    p = (int*) Queue_end(q);
    printf("end %d\n", *p);
    
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
