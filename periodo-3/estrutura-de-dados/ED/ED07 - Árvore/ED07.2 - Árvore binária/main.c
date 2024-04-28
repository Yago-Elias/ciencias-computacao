#include <stdio.h>
#include "binary-tree.h"

int main() {
  BST *bst = BST_alloc();

  BST_insert(bst, 3);
  BST_insert(bst, 2);
  BST_insert(bst, 1);
  BST_insert(bst, 9);
  BST_insert(bst, 7);
  BST_insert(bst, 6);
  BST_insert(bst, 8);
  BST_insert(bst, 15);
  BST_insert(bst, 12);
  BST_insert(bst, 17);

  BST_print(bst);
  printf("\n");

  BST *node = BST_search(bst, 6);
  BST_print(node);
  printf("\n");

  bst = BST_remove(bst, 4, NULL);

  BST_free(bst);

  return 0;
}
