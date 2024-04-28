#include <stdio.h>
#include "tree.h"

int height_tree(Tree *tr) {
  int h1 = 0, h2;
  if (tr) {
    h1 = height_tree(tr->left);
    h2 = height_tree(tr->right);
    if (h1 > h2)
      return h1;
    else
      return h2;
  }
}

int main() {
Tree *tr = Tree_alloc(7,
	Tree_alloc(2, NULL,
			Tree_alloc(9, NULL, NULL)),
	Tree_alloc(5,
			Tree_alloc(3, NULL, NULL),
			Tree_alloc(1, NULL, NULL)));

  return 0;
}
