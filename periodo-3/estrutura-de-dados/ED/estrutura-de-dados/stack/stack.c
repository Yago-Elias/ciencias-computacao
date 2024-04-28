#include <stdio.h>
#include <stdlib.h>
#include "stack.h""

struct Stack
{
	int size;
	int top;
	void **elements;
};

Stack *Stack_alloc(int size)
{
	Stack *stk = malloc(sizeof(Stack));

	if (stk)
	{
		stk->size = size;
		stk->top = -1;
		stk->elements = calloc(size, sizeof(void));
	}
	return stk;
}

void Stack_free(Stack *stk)
{
	if (stk)
	{
		free(stk->elements);
		free(stk);
	}
}

int Stack_isEmpty(Stack *stk)
{
	if (stk)
		return stk->top == -1;
	return 0;
}

int Stack_isFull(Stack *stk)
{
	if (stk)
		return stk->top == (stk->size-1);
	return 0;
}

void Stack_push(Stack *stk, void *element)
{
	if (stk)
		if (!Stack_isFull(stk))
		{
			stk->top++;
			stk->elements[stk->top] = element;
		}
}

void *Stack_pop(Stack *stk)
{
	void *element = NULL;

	if (stk)
	{
		if (!Stack_isEmpty(stk))
		{
			element = stk->elements[stk->top];
			stk->top--;
		}
	}
	return element;
}

void *Stack_top(Stack *stk)
{
	if (stk)
		return stk->elements[stk->top];
	return 0;
}

void Stack_print(Stack *stk, void (*print)(void *))
{
	int i;

	if (stk)
	{
		for (i = stk->top; i >= 0; i--)
			print(stk->elements[i]);
	}
}
