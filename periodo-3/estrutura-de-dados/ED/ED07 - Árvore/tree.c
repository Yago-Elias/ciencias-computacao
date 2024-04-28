#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Tree *Tree_alloc(int value, Tree *left, Tree *right) {
  Tree *tr = malloc(sizeof(Tree));

  if (tr) {
    tr->value = value;
    tr->left = left;
    tr->right = right;
  }

  return tr;
}

void Tree_free(Tree *tr) {
  if (tr) {
    Tree_free(tr->left);
    Tree_free(tr->right);
    free(tr);
  }
}

void Tree_print(Tree *tr) {
  if (tr) {
    printf(" <%c ", tr->value);
    Tree_print(tr->left);
    Tree_print(tr->right);
    printf(" > ");
  }
  else printf("<>");
}
