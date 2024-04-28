typedef struct BST BST;

struct BST {
  int value;
  BST *left;
  BST *right;
};

BST *BST_alloc();
void BST_free(BST *bst);
void BST_insert(BST *bst, int value);
BST *BST_search(BST *bst, int value);
BST *BST_remove(BST *bst, int value);
void BST_print(BST *bst);