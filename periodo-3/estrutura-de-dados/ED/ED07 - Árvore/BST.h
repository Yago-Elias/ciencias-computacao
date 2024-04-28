typedef struct BST BST;

BST  *BST_alloc(int (*compar)(void*, void*));
void  BST_free(BST *bst);
void  BST_insert(BST *bst, void *value);
void *BST_search(BST *bst, void *value);
BST  *BST_remove(BST *bst, void *value);
void  BST_print(BST *bst, void (*print)(void*));
