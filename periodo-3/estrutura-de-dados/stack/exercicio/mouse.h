#include "../stack.h"

typedef struct pos {
	int x, y;
} Pos;

void run();
Pos *starting_position(Stack *stk, int l[][11]);
void print_labirinto(int l[][11]);
void move(Stack *stk, int l[][11]);
int leave(Pos *p);
