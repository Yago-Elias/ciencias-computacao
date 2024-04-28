#include <stdio.h>
#include "tree.h"

int main() {
  Tree *tr = Tree_alloc('a',
	Tree_alloc('b', NULL,
			Tree_alloc('d', NULL, NULL)),
	Tree_alloc('c',
			Tree_alloc('e', NULL, NULL),
			Tree_alloc('f', NULL, NULL)));
  Tree_print(tr);
  printf("\n");

  Tree_free(tr);

  return 0;
}
