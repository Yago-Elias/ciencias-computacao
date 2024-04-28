#include <stdio.h>
#include <stdlib.h>
#include "BST.h"
#define TEST

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
    BST *new = NULL;
    
    if (bst && value) {
        if (bst->value == 0)
            bst->value = value;
        else {
            if (bst->value < value) {
                if (bst->right == NULL) {
                   new = BST_alloc(); 
                   new->value = value;
                   bst->right = new;
                }
                else {
                    BST_insert(bst->right, value);
                }
            }
            else if (bst->value > value) {
                if (bst->left == NULL) {
                   new = BST_alloc(); 
                   new->value = value;
                   bst->left = new;
                }
                else {
                    BST_insert(bst->left, value);
                }
            }
        }
    }
}

BST *BST_search(BST *bst, int value) {
    if (bst && value) {
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

BST *BST_remove(BST *bst, int value) {
    BST *aux = NULL, *n = NULL;
    
    if (bst && value) {
        if (bst->value == value) {
            if (bst->left && bst->right) {
                
                n = bst->left;
                while (n->right) {
                    aux = n;
                    n = n->right;
                }
                
                if (aux) {
                    aux->right = n->left;
                    n->left = bst->left;
                }
                
                n->right = bst->right;
                free(bst);
                return n;
            }
            else if (bst->left) {
                aux = bst->left;
                free(bst);
                return aux;
            }
            else if (bst->right) {
                aux = bst->right;
                free(bst);
                return aux;
            }
            else {
                free(bst);
                return NULL;
            }
        }
        else if (bst->value < value) {
            bst->right = BST_remove(bst->right, value);
        }
        else if (bst->value > value) {
            bst->left = BST_remove(bst->left, value);
        }
    }
    return bst;
}

void BST_print(BST *bst) {
    if (bst) {
        printf("(%d ", bst->value);
        BST_print(bst->left);
        BST_print(bst->right);
        printf(") ");
    }
    else
		printf("~ ");
}

BST *BST_min(BST *bst) {
    BST *n = NULL;
    
    if (bst) {
        
        if (bst->left) {
            n = bst->left;
            while (n->left) {
                n = n->left;
            }
        }
        else
          return bst;
    }
    
    return n;
}

int BST_isIn(BST *bst, int value) {

    while (bst) {
        if (bst->value == value)
            return 1;
        
        if (value > bst->value)
            bst = bst->right;
        else
            bst = bst->left;
    }
    
    return 0;
}

void BST_vecToBST(BST *bst, int vec[], int begin, int end) {
    int center = (begin+end)/2;
    BST_insert(bst, vec[center]);
    
    if (begin != center)
        BST_vecToBST(bst, vec, begin, center-1);
    
    if (end != center)    
        BST_vecToBST(bst, vec, center+1, end);
}

#ifdef TEST
/*
int main() {
    BST *b = BST_alloc(), *busca, *min;
    BST_insert(b, 1);
    BST_insert(b, 7);
    BST_insert(b, 3);
    BST_insert(b, 6);
    BST_insert(b, 2);
    BST_print(b);
    printf("\n");
    
    busca = BST_search(b, 6);
    printf("%p %d\n", busca, busca->value);
    
    busca = BST_search(b, 8);
    printf("%p\n", busca);
    
    min = BST_min(b);
    printf("%p %d\n", min, min->value);
    
    printf("%s\n", BST_isIn(b, 7) ? "Sim" : "Não");
    printf("%s\n", BST_isIn(b, 11) ? "Sim" : "Não");
    
    //         0 1 2 3 4 5 6
    int n[] = {1,2,3,4,5,6,7};
    BST *c = BST_alloc();
    
    BST_vecToBST(c, n, 0, 6);
    BST_print(c);
    printf("\n");
    
    c = BST_remove(c, 3);
    BST_print(c);
    printf("\n");
    
    c = BST_remove(c, 4);
    BST_print(c);
    printf("\n");
    
    BST_free(b);
    BST_free(c);
    return 0;
}
*/
#endif