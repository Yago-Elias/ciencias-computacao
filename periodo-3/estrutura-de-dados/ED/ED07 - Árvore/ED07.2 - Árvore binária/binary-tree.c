#include <stdio.h>
#include <stdlib.h>
#include "binary-tree.h"

BST *BST_alloc() {
  BST *bst = malloc(sizeof(BST));

  if (bst) {
    bst->value = 0;
    bst->left = NULL;
    bst->right = NULL;
  }

  return bst;
}

void BST_free(BST *bst) {
  if (bst) {
    BST_free(bst->left);
    BST_free(bst->right);
    free(bst);
  }
}

void BST_insert(BST *bst, int value) {
  BST *new_bst = NULL;

  if (bst && value) {
    if (bst->value == 0) {
      bst->value = value;
    }
    else {
      if (bst->value > value) {
        if (bst->left == NULL) {
          bst->left = BST_alloc();
          bst->left->value = value;
        } else {
          BST_insert(bst->left, value);
        }
      }
      else if (bst->value < value) {
        if (bst->right == NULL) {
          bst->right = BST_alloc();
          bst->right->value = value;
        } else {
          BST_insert(bst->right, value);
        }
      }
    }
  }
}

BST *BST_search(BST *bst, int value) {
  if (bst) {
    if (bst->value == value) {
      return bst;
    }
    else if (bst->value > value) {
      return BST_search(bst->left, value);
    }
    else if (bst->value < value) {
      return BST_search(bst->right, value);
    }
  }

  return NULL;
}

BST *BST_remove(BST *bst, int value, BST *parent) {
  BST *p = NULL, *q = NULL, *aux_node = NULL;

  if (bst && value) {
    if (bst->value == value) {
      if (bst->left == NULL) {
        aux_node = bst->right;
        free(bst);
        return aux_node;
      }
      else if (bst->right == NULL) {
        aux_node = bst->left;
        free(bst);
        return aux_node;
      }
    }
    else {
      p = bst;
      q = bst->left;
      while (q->right) {
        p = q;
        q = q->right;
      }
       if (p != bst) {
        p->right = q->left;
        q->left = bst->left;
      }

      q->right = bst->right;
      free(bst);
      return q;
    }
  }
}

void BST_print(BST *bst) {
  if (bst) {
    BST_print(bst->left);
    printf("%d  ", bst->value);
    BST_print(bst->right);
  }
}
