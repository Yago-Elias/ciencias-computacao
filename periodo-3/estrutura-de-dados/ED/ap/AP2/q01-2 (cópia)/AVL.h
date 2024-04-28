/*** File AVL.h - AVL Tree ***/
/*
 *   Shane Saunders
 */
#ifndef AVL_H
#define AVL_H


/* Size of the stack used for storing path travesersed through the tree.
 * This should be defined to be plenty large enough to accomodate the maximum
 * practical tree depth which could be expected.
 */
#define AVL_STACK_SIZE 1000


/* Structure type for nodes in the AVL tree. */
typedef struct AVL_node {
    void *item;
    struct AVL_node *left, *right;
    signed char balance;
} AVL_node;

/* Structure type for the AVL tree. */
typedef struct AVL {
    AVL_node *root;
    int n;
    int (* compar)(const void *, const void *);
    AVL_node **stack;
    signed char *path_info;
} AVL;

/* AVL_alloc() - Allocates space for a AVL tree and returns a pointer to it.
 * The function compar compares they keys of two items, and returns a negative,
 * zero, or positive integer depending on whether the first item is less than,
 * equal to, or greater than the second.
 */
AVL *AVL_alloc(int (* compar)(const void *, const void *));

/* AVL_free() - Frees space used by the AVL tree pointed to by t. */
void AVL_free(AVL *t);

/* AVL_insert() - Inserts an item into the AVL tree pointed to by t,
 * according the the value its key.  The key of an item in the AVL tree must
 * be unique among items in the tree.  If an item with the same key already
 * exists in the tree, a pointer to that item is returned.  Otherwise, NULL is
 * returned, indicating insertion was successful.
 */
void *AVL_insert(AVL *t, void *item);

/* AVL_find() - Find an item in the AVL tree with the same key as the
 * item pointed to by `key_item'.  Returns a pointer to the item found, or NULL
 * if no item was found.
 */
void *AVL_find(AVL *t, void *key_item);

/* AVL_find_min() - Returns a pointer to the minimum item in the AVL
 * tree pointed to by t.  If there are no items in the tree a NULL pointer is
 * returned.
 */
void *AVL_find_min(AVL *t);

/* AVL_delete() - Delete the first item found in the AVL tree with
 * the same key as the item pointed to by `key_item'.  Returns a pointer to the
 * deleted item, and NULL if no item was found.
 */
void *AVL_delete(AVL *t, void *key_item);

/* AVL_delete_min() - Deletes the item with the smallest key from the AVL
 * tree pointed to by t.  Returns a pointer to the deleted item.
 * Returns a NULL pointer if there are no items in the tree.
 */
void *AVL_delete_min(AVL *t);

#endif
