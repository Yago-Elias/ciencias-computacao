#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../stack.h"
#include "mouse.h"

void run() {
	Stack *stk = Stack_alloc(30);
	Pos *pos = NULL;
	int i, j, labirinto[11][11];

	for (i = 0; i < 11; i++)
		for (j = 0; j < 11; j++)
			scanf(" %d", &labirinto[i][j]);

	pos = starting_position(stk, labirinto);
	Stack_push(stk, pos);

	do {
		print_labirinto(labirinto);
		move(stk, labirinto);
		pos = Stack_top(stk);
		sleep(1);
	} while (!leave(pos));
	print_labirinto(labirinto);
}

void print_labirinto(int l[][11]) {
	int c_ft, c_pf;

	printf("\033[1J\033[1H");
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			switch (l[i][j]) {
				case 0:
				c_pf = 0;
				break;
				case 1:
				c_ft = 34;
				c_pf = 44;
				break;
				case 2:
				c_pf = 102;
				break;
				case 3:
				printf("\U0001f42d");
				break;
				case 4:
				c_ft = 32;
				c_pf = 43;
				break;
			}
			if (l[i][j] != 3)
				printf("\033[%d;%dm%2d\033[m", c_ft, c_pf, l[i][j]);
		}
		printf("\n");
	}
}

Pos *starting_position(Stack *stk, int l[][11])
{
	srand(time(NULL));
	Pos *pos = malloc(sizeof(Pos));

	while (1) {
		pos->x = rand() % 11;
		pos->y = rand() % 11;
		if (l[pos->x][pos->y] == 0) break;
	}
	l[pos->x][pos->y] = 3;
	return pos;
}


void print(void *p) {
	Pos *pos = (Pos *) = p;
	if (pos) {
		printf("\e[50;1%d, %d", p->x, p->y);
	}
}

void move(Stack *stk, int l[][11]) {
	Pos *p1 = malloc(sizeof(Pos));
	Pos *p2 = malloc(sizeof(Pos));
	p1 = Stack_top(stk);
	p2 = p1;

	if (p1) {
		l[p1->x][p1->y] = 4;
		if (l[p1->x][p1->y+1] == 0 || l[p1->x][p1->y+1] == 2) {
			p1->y++;
			Stack_push(stk, p1);
		}
		else if (l[p1->x][p1->y-1] == 0 || l[p1->x][p1->y-1] == 2) {
			p1->y--;
			Stack_push(stk, p1);
		}
		else if (l[p1->x+1][p1->y] == 0 || l[p1->x+1][p1->y] == 2) {
			p1->x++;
			Stack_push(stk, p1);
		}
		else if (l[p1->x-1][p1->y] == 0 || l[p1->x-1][p1->y] == 2) {
			p1->x--;
			Stack_push(stk, p1);
		}
		else {
			p1 = Stack_pop(stk);
			Stack_print(stk, print);
			p2 = Stack_top(stk);
			printf("\e60H");
			Stack_print(stk, print);
			l[p1->x][p1->y] = 4;
			l[p2->x][p2->y] = 3;
		}
		// if (p1 != p2) {
		// 	int static x = 2;
		// 	printf("\e[1;30Hem frente\e[1H");
		// 	printf("\e[%d;33H%d, %d\e[1H", x, p1->x, p1->y);
		// 	x++;
		// }
		// else {
		// 	int static y = 2;
		// 	printf("\e[1;40H| voltar\e[1H");
		// 	printf("\e[%d;43H%d, %d\e[1H", y, p1->x, p1->y);
		// 	y++;
		// }
	}
}

int leave(Pos *p) {
	return (p->x == 3 && p->y == 0);
}
