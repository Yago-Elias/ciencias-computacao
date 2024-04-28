#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Queue.h"
#define tam 100

//gcc main.c Queue.c -c && gcc main.o Queue.o && ./a.out

int main() {
	Queue *q = Queue_alloc(tam);
	int aleatorio;
	srand(time(NULL));
	
	for (int i = 0; i < tam; i++)
	{
		aleatorio = (rand() % 100) + 1;
		Queue_push(q, aleatorio);
	}
	
	Queue_print(q);
	
	Queue_free(q);
	return 0;
}