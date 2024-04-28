/*** File RB.h - Red-Black Tree ***/
/*
 *   Shane Saunders
 */
#ifndef RB_H
#define RB_H
#define RB_STACK_SIZE 1000

typedef struct {
	int chave;
	char letra[0];
} letras;

typedef enum {Red,Black} RB_colour;

/* Structure type for nodes in the red-black tree. */
typedef struct RB_node {
    void *item;
    struct RB_node *left, *right;
    RB_colour colour;
} RB_node;

/* Structure type for the red-black tree. */
typedef struct RB {
    RB_node *root;
    int n;
    int (* compar)(const void *, const void *);
    RB_node **stack;
} RB;


/* RB_alloc() - Allocates space for a red-black tree and returns a pointer
 * to it.  The function compar compares they keys of two items, and returns a
 * negative, zero, or positive integer depending on whether the first item is
 * less than, equal to, or greater than the second.
 */
RB *RB_alloc(int (* compar)(const void *, const void *));

/* RB_free() - Frees space used by the red-black tree pointed to by t. */
void RB_free(RB *t);

/* RB_insert() - Inserts an item into the red-black tree pointed to by t,
 * according the the value its key.  The key of an item in the red-black
 * tree must be unique among items in the tree.  If an item with the same key
 * already exists in the tree, a pointer to that item is returned.  Otherwise,
 * NULL is returned, indicating insertion was successful.
 */
void *RB_insert(RB *t, void *item);

/* RB_find() - Find an item in the red-black tree with the same key as the
 * item pointed to by `key_item'.  Returns a pointer to the item found, or NULL
 * if no item was found.
 */
void *RB_find(RB *t, void *key_item);

/* RB_find_min() - Returns a pointer to the minimum item in the red-black
 * tree pointed to by t.  If there are no items in the tree a NULL pointer is
 * returned.
 */
void *RB_find_min(RB *t);

/* RB_delete() - Delete an item in the red-black tree with the same key as
 * the item pointed to by `key_item'.  Returns a pointer to the  deleted item,
 * and NULL if no item was found.
 */
void *RB_delete(RB *t, void *key_item);

/* RB_delete_min() - Deletes the item with the smallest key from the binary
 * search tree pointed to by t.  Returns a pointer to the deleted item.
 * Returns a NULL pointer if there are no items in the tree.
 */
void *RB_delete_min(RB *t);

#endif
