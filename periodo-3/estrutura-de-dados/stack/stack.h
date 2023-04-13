typedef struct Stack Stack;

Stack *Stack_alloc(int size);
void Stack_free(Stack *stk);
int Stack_isEmpty(Stack *stk);
int Stack_isFull(Stack *stk);
void Stack_push(Stack *stk, void *element);
void *Stack_pop(Stack *stk);
void *Stack_top(Stack *stk);

void Stack_print(Stack *stk, void (*print)(void *));
