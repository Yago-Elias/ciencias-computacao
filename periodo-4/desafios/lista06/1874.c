#include <stdio.h>
#include <stdlib.h>

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

int main() {
	int h, p, e, a=0, f=0;
	Stack **stk;

	while (1) {
		scanf("%d%d%d", &h, &p, &e);
		if (h == 0 && p == 0 && e == 0) {
			for (int i = 0; i < p; ++i)
				free(stk[i]);
			free(stk);
			return 0;
		}

		if (a == 0)
			stk = malloc(p * sizeof(Stack *));
		else if (p > a)
			stk = realloc(stk, p);

		for (int i = a; i < p; ++i)
			stk[i] = malloc(p * sizeof(Stack));

		a = p;
		if (p > m) m = p;
	}
}