#include <stdio.h>
#include "tree.h"

int find_father(Tree *tr, int son, Tree *parent) {
  int father = 0;

  if (tr) {
    if (tr->value == son) {
      if (parent)
        return parent->value;
      else
	return find_father(tr->left, son, tr) + find_father(tr->right, son, tr);
    }
  }
}

int main() {
Tree *tr = Tree_alloc(7,
	Tree_alloc(2, NULL,
			Tree_alloc(9, NULL, NULL)),
	Tree_alloc(5,
			Tree_alloc(3, NULL, NULL),
			Tree_alloc(1, NULL, NULL)));

  printf("Father: %d\n", find_father(tr, 9, NULL));
  return 0;
}
