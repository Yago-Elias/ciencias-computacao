typedef struct Queue Queue;

Queue *Queue_alloc(int size);
void   Queue_free(Queue * q);
int    Queue_isEmpty(Queue * q);
int    Queue_isFull(Queue * q);
void   Queue_push(Queue *q , int item);
int    Queue_pop(Queue * q);
int    Queue_begin(Queue * q);
int    Queue_end(Queue * q);
void   Queue_print(Queue *q);
