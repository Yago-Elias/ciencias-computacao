/*** File AVL.c - AVL Tree ***/
/*
 *   Shane Saunders
 */
#include <stdlib.h>
#include "AVL.h"

/* Test implementation which uses the stack history to replace the use of next
 * and prev pointers.
 */

/* AVL_alloc() - Allocates space for a AVL tree and returns a pointer to it.
 * The function compar compares they keys of two items, and returns a negative,
 * zero, or positive integer depending on whether the first item is less than,
 * equal to, or greater than the second.
 */
AVL *AVL_alloc(int (*compar)(const void *, const void *)) {
    AVL *t;

    t = malloc(sizeof(AVL));
    t->root = NULL;
    t->compar = compar;
    t->stack = malloc(AVL_STACK_SIZE * sizeof(AVL_node *));
    t->path_info = malloc(AVL_STACK_SIZE * sizeof(signed char));
    t->n = 0;

    return t;
}

/* AVL_free() - Frees space used by the AVL tree pointed to by t. */
void AVL_free(AVL *t) {
    int tos;
    AVL_node *p, **stack;

    /* In order to free all nodes in the tree a depth first search is performed
     * This is implemented using a stack.
     */
    if (t->root) {
        stack = t->stack;
        stack[0] = t->root;
        tos = 1;
        while (tos) {
            p = stack[--tos];
            if (p->left) {
                stack[tos++] = p->left;
            }
            if (p->right) {
                stack[tos++] = p->right;
            }
            free(p);
        }
    }

    free(t->stack);
    free(t->path_info);
    free(t);
}

/* AVL_insert() - Inserts an item into the AVL tree pointed to by t,
 * according the the value its key.  The key of an item in the AVL tree must
 * be unique among items in the tree.  If an item with the same key already
 * exists in the tree, a pointer to that item is returned.  Otherwise, NULL is
 * returned, indicating insertion was successful.
 */
void *AVL_insert(AVL *t, void *item) {
    int (*compar)(const void *, const void *);
    int cmp_result;
    void *return_result;
    AVL_node *x, *p, *q, *r, **attach_x;
    AVL_node **stack;
    int tos, stack_n;
    signed char *path_info;

    compar = t->compar;

    /* The stack stores information about the path to a node.  For the array
     * stack, stack[i] holds the (i)th nodes on the path from the root, with
     * the 0th node being the root node.  For the array path_info[],
     * path_info[i] is -1 or 1 depending on whether the left or right branch
     * branch was traversed from the (i)th node.  The path_info array can then
     * be used for updating balance information.
     */
    stack = t->stack;
    path_info = t->path_info;
    tos = 0;

    /* Search for insertion position, starting from the root node, if it
     * exists.
     */
    if ((p = t->root)) {
    /* Repeatedly explore either the left branch or the right branch
	 * depending on the value of the key, until an empty branch position
	 * is found.
	 */
        for (;;) {
            stack[tos] = p;
            cmp_result = compar(item, p->item);
            if (cmp_result < 0) {
                path_info[tos] = -1;
                tos++;
                p = p->left;
                if (!p) {
                    attach_x = &stack[tos - 1]->left;
                    break;
                }
            }
            else if (cmp_result > 0) {
                path_info[tos] = 1;
                tos++;
                p = p->right;
                if (!p) {
                    attach_x = &stack[tos - 1]->right;
                    break;
                }
            }
            else {
                return p->item;
            }
        }
    }
    else {
        attach_x = &t->root;
    }

    /* Null will be returned, indicating there was no item with the same key in
     * the tree.
     */
    return_result = NULL;

    /* Allocated space for the new node. */
    x = malloc(sizeof(AVL_node));
    x->left = x->right = NULL;
    x->balance = 0;
    x->item = item;

    /* attach_x is a pointer to the pointer variable to add the node to the
     * tree.
     */
    *attach_x = x;
    t->n++;

    /* Now traverse the stack, updating balance information of ancestors,
     * and performing rotation if necessary.
     */
    stack_n = tos;
    while (tos) {
        p = stack[--tos];
        if (p->balance == 0) {
           /* Balance changes from 0 to 1 or -1.  The length of the
            * longest path from  p to a leaf has increased by 1, so
            * continue the iteration to the parent of p.
            */
            p->balance += path_info[tos];
        }
        else {
            p->balance += path_info[tos];
            if (p->balance == 0) {
               /* The balance has changed from -1 or 1 to 0.  The length
                * of the longest path from p to a leaf has not changed,
                * so stop the iteration.
                */
                break; /* Tree is balanced. */
            }
            else {
               /* Balance changes from 1 to 2 or from -1 to -2.
                * Now the tree is unbalanced, and rotation must be
                * performed.
                *
                * For this description, define direction x as the
                * direction of the over-balance, and direction y, as the
                * other direction.   For this description it is simpler to
                * refer to the x child and the y child, since the use left
                * and right depends on the tree balance.
                */

               /* The kind of rotation that occurs depends on whether
                * the balance of p's child (from which p was reached), q,
                * is in the same direction as the balance of p.
                * This is determined by looking at path_info[tos].
                */
                q = stack[tos + 1];
                if (path_info[tos] == path_info[tos + 1]) {
                   /* There is the the following tree structure:
                    *  A - x child tree of q.
                    *  B - y child tree of q.
                    *  C - y child of p.
                    */

                   /* For the rotation:
                    *  - tree B replaces node q as the child of p.
                    *  - node p replaces tree B as the child of q.
                    */
                    if (path_info[tos] == 1) {
                        p->right = q->left;
                        q->left = p;
                    }
                    else {
                        p->left = q->right;
                        q->right = p;
                    }

                    p->balance = q->balance = 0;

                   /* A child pointer of p's parent changes from p to q.
                    * If p was the root, the root node changes.
                    */
                    if (tos != 0) {
                        if (path_info[tos - 1] == 1) {
                            stack[tos - 1]->right = q;
                        }
                        else {
                            stack[tos - 1]->left = q;
                        }
                    }
                    else {
                        t->root = q;
                    }

                    break;
                }
                else {
                    if (tos + 2 != stack_n) {
                        r = stack[tos + 2];
                    }
                    else {
                        r = x; /* Special case: r is the inserted node. */
                    }
                    /* There is the following tree structure:
                    *  A - x child tree of q.
                    *  B - x child tree of r.
                    *  C - y child tree of r.
                    *  D - y child tree of p.
                    */

                    /* For the rotation:
                    *  - tree B replaces node r as the child of q.
                    *  - tree C replaces node q as the child of p.
                    *  - node q replaces tree B as the child of r.
                    *  - node p replaces tree C as the child of r.
                    */
                    if (path_info[tos] == 1) {
                        q->left = r->right;
                        p->right = r->left;
                        r->right = q;
                        r->left = p;
                        if (r->balance == 1) {
                            p->balance = -1;
                            q->balance = 0;
                        }
                        else if (r->balance == -1) {
                            p->balance = 0;
                            q->balance = 1;
                        }
                        else {
                            p->balance = q->balance = 0;
                        }
                    }
                    else {
                        q->right = r->left;
                        p->left = r->right;
                        r->left = q;
                        r->right = p;
                        if (r->balance == 1) {
                            p->balance = 0;
                            q->balance = -1;
                        }
                        else if (r->balance == -1) {
                            p->balance = 1;
                            q->balance = 0;
                        }
                        else {
                            p->balance = q->balance = 0;
                        }
                    }
                    r->balance = 0;

                    /* A child pointer of p's parent changes from p to r.
                    * If p was the root, the root node changes.
                    */
                    if (tos != 0) {
                        if (path_info[tos - 1] == 1) {
                            stack[tos - 1]->right = r;
                        }
                        else {
                            stack[tos - 1]->left = r;
                        }
                    }
                    else {
                        t->root = r;
                    }
                    break;
                }
            }
        }
    }

    return return_result;
}

/* AVL_find() - Find an item in the AVL tree with the same key as the
 * item pointed to by `key_item'.  Returns a pointer to the item found, or NULL
 * if no item was found.
 */
void *AVL_find(AVL *t, void *key_item) {
    int (*compar)(const void *, const void *);
    int cmp_result;
    AVL_node *p, *next_p;

    if ((next_p = t->root)) {
        compar = t->compar;

        /* Repeatedly explore either the left or right branch, depending on the
        * value of the key, until the correct item is found.
        */
        do {
            p = next_p;
            cmp_result = compar(key_item, p->item);
            if (cmp_result < 0) {
                next_p = p->left;
            }
            else if (cmp_result > 0) {
                next_p = p->right;
            }
            else {
                /* Item found. */
                return p->item;
            }
        } while (next_p);
    }

    return NULL;
}

/* AVL_find_min() - Returns a pointer to the minimum item in the AVL
 * tree pointed to by t.  If there are no items in the tree a NULL pointer is
 * returned.
 */
void *AVL_find_min(AVL *t) {
    AVL_node *p, *next_p;

    if ((next_p = t->root)) {
        /* To locate the minimum, the left branches is repeatedly chosen until
	    * we can explore no further.
         */
        do {
            p = next_p;
            next_p = p->left;
        } while (next_p);
    }
    else {
        return NULL;
    }

    return p->item;
}

/* AVL_delete() - Delete the first item found in the AVL tree with
 * the same key as the item pointed to by `key_item'.  Returns a pointer to the
 * deleted item, and NULL if no item was found.
 */
void *AVL_delete(AVL *t, void *key_item) {
    void *return_item;
    int (*compar)(const void *, const void *);
    int cmp_result;
    AVL_node *p, *prev_p;
    AVL_node *m, *prev_m;
    AVL_node *q, *r;
    AVL_node **stack;
    int tos, stack_p;
    signed char *path_info;

    /* If the tree is empty return NULL. */
    if (!(p = t->root))
        return NULL;

    compar = t->compar;

    /* The stack stores information about the path to a node.  For the array
     * stack, stack[i] holds the (i)th nodes on the path from the root, with
     * the 0th node being the root node.  For the array path_info[],
     * path_info[i] is -1 or 1 depending on whether the left or right branch
     * branch was traversed from the (i)th node.  The path_info[] array can
     * then be used for updating balance information.
     */
    stack = t->stack;
    path_info = t->path_info;
    tos = 0;

    /* Attempt to locate the item to be deleted. */
    for (;;) {
        cmp_result = compar(key_item, p->item);
        if (cmp_result < 0) {
            path_info[tos] = -1;
            stack[tos++] = p;
            p = p->left;
        }
        else if (cmp_result > 0) {
            path_info[tos] = 1;
            stack[tos++] = p;
            p = p->right;
        }
        else {
            /* Item found. */
            break;
        }
        if (!p) {
            /* Item not found. */
            return NULL;
        }
    }

    /* p points to the node to be deleted.  Currently, prev_p is on the top of
     * the stack.
     */
    if (!p->left) {
        /* Right child replaces p. */
        if (tos == 0) {
            t->root = p->right;
        }
        else {
            prev_p = stack[tos - 1];
            if (p == prev_p->left) {
                prev_p->left = p->right;
            }
            else {
                prev_p->right = p->right;
            }
        }
    }
    else if (!p->right) {
        /* Left child replaces p. */
        if (tos == 0) {
            t->root = p->left;
        }
        else {
            prev_p = stack[tos - 1];
            if (p == prev_p->left) {
                prev_p->left = p->left;
            }
            else {
                prev_p->right = p->left;
            }
        }
    }
    else {
        /* Minimum child, m, in the right subtree replaces p. */
        path_info[tos] = 1;
        stack[tos] = p;
        stack_p = tos++; /* Save the stack position of p. */

        m = p->right; /* Guaranteed not to be NULL. */
        do {
            path_info[tos] = -1;
            stack[tos++] = m;
            m = m->left;
        } while (m);
        m = stack[--tos];

        /* Update either the left or right child pointers of prev_p. */
        if (stack_p == 0) {
            t->root = m;
        }
        else {
            prev_p = stack[stack_p - 1];
            if (p == prev_p->left) {
                prev_p->left = m;
            }
            else {
                prev_p->right = m;
            }
        }

        /* Update the tree part m was removed from, and assign m the child
        * pointers of p (only if m is not the right child of p).
        */
        prev_m = stack[tos - 1];
        if (prev_m != p) {
            prev_m->left = m->right;
            m->right = p->right;
        }
        m->left = p->left;

        /* Give node m the balance node p had, and replace the stack entry for
        * p with m.
        */
        m->balance = p->balance;
        stack[stack_p] = m;
    }

    /* Get return value and free space used by node p. */
    return_item = p->item;
    free(p);
    t->n--;

    /* Perform rotations if necessary to rebalance the tree.  This is done
     * by traversing the stack, updating balance information of ancestors,
     * and performing rotations if necessary.
     *
     * Pointer p now points to the node being considered for rebalance.
     */
    while (tos) {
        p = stack[--tos];
        if (p->balance == 0) {
            /* Balance changes from 0 to 1 or -1.  The length of only one
            * path from p to a leaf has decreased by 1, so the length of the
            * longest path is unchanged.  Therefore iteration can stop.
            */
            p->balance -= path_info[tos];
            break; /* Tree is balanced. */
        }
        else {
            p->balance -= path_info[tos];

            /* Note that if balance changed from -1 or 1 to 0, the length of
            * the longest path from p to a leaf must have decreased.
            * Therefore iterations for balance updates will continue.
            */

            if (p->balance != 0) {
                /* Balance changes from 1 to 2 or from -1 to -2.
                * Now the tree is unbalanced, and rotation must be
                * performed.
                *
                * For this description, define direction x as the
                * direction of the over-balance, and direction y, as the
                * other direction.   For this description it is simpler to
                * refer to the x child and the y child, since the use left
                * and right depends on the tree balance.
                */

                /* The kind of rotation that occurs depends on whether
                * the balance of p's other child (not the child p was reached
                * from) is in the same direction as the balance of p.
                */
                if (path_info[tos] == 1) {
                    q = p->left; /* p's other child. */
                }
                else {
                    q = p->right; /* p's other child. */
                }
                if (path_info[tos] != q->balance) {
                    /* The balance (p, q) will be either:
                    * (2,1), (2,0), (-2,-1), or (-2,0)
                    */

                    /* There is the the following tree structure:
                    *  A - x child tree of q.
                    *  B - y child tree of q.
                    *  C - y child of p.  (Deletion occurred in tree C.)
                    */

                    /* For the rotation:
                    *  - tree B replaces node q as the child of p.
                    *  - node p replaces tree B as the child of q.
                    */
                    if (path_info[tos] != 1) {
                        p->right = q->left;
                        q->left = p;
                    }
                    else {
                        p->left = q->right;
                        q->right = p;
                    }

                    /* A child pointer of p's parent changes from p to q.
                    * If p was the root, the root node changes.
                    */
                    if (tos != 0) {
                        if (path_info[tos - 1] == 1) {
                            stack[tos - 1]->right = q;
                        }
                        else {
                            stack[tos - 1]->left = q;
                        }
                    }
                    else {
                        t->root = q;
                    }

                    /* Update balance information of nodes p and q. */
                    if (q->balance == 0) {
                        p->balance = p->balance > 0 ? 1 : -1;
                        q->balance = -p->balance;
                        break; /* Tree is balanced. */
                    }
                    else {
                        p->balance = q->balance = 0;
                    }

                    /* Unless q->balance == 0, iterations will continue, since
                    * the length of longest path has decreased.
                    */
                }
                else {
                    /* The balance of (p, q) will be either:
                    * (2,-1) or (-2,1)
                    */

                    /* There is the following tree structure:
                    *  A - x child tree of q.
                    *  B - x child tree of r.
                    *  C - y child tree of r.
                    *  D - y child tree of p.  (Deletion occurred in tree D)
                    */

                    /* For the rotation:
                    *  - tree B replaces node r as the child of q.
                    *  - tree C replaces node q as the child of p.
                    *  - node q replaces tree B as the child of r.
                    *  - node p replaces tree C as the child of r.
                    */
                    if (path_info[tos] != 1) {
                        r = q->left;
                        q->left = r->right;
                        p->right = r->left;
                        r->right = q;
                        r->left = p;
                        if (r->balance == 1) {
                            p->balance = -1;
                            q->balance = 0;
                        }
                        else if (r->balance == -1) {
                            p->balance = 0;
                            q->balance = 1;
                        }
                        else {
                            p->balance = q->balance = 0;
                        }
                    }
                    else {
                        r = q->right;
                        q->right = r->left;
                        p->left = r->right;
                        r->left = q;
                        r->right = p;
                        if (r->balance == 1) {
                            p->balance = 0;
                            q->balance = -1;
                        }
                        else if (r->balance == -1) {
                            p->balance = 1;
                            q->balance = 0;
                        }
                        else {
                            p->balance = q->balance = 0;
                        }
                    }
                    r->balance = 0;

                    /* A child pointer of p's parent changes from p to r.
                    * If p was the root, the root node changes.
                    */
                    if (tos != 0) {
                        if (path_info[tos - 1] == 1) {
                            stack[tos - 1]->right = r;
                        }
                        else {
                            stack[tos - 1]->left = r;
                        }
                    }
                    else {
                        t->root = r;
                    }

                    /* Continue with further iterations, since the length of
                    * longest path has decreased.
                    */
                }
            }
        }
    }

    return return_item;
}

/* AVL_delete_min() - Deletes the item with the smallest key from the AVL
 * tree pointed to by t.  Returns a pointer to the deleted item.
 * Returns a NULL pointer if there are no items in the tree.
 */
void *AVL_delete_min(AVL *t) {
    void *return_item;
    AVL_node *p;
    AVL_node *q, *r;
    AVL_node **stack;
    int tos;

    /* The stack stores information about the path to a node.  For the array
     * stack, stack[i] holds the (i)th nodes on the path from the root, with
     * the 0th node being the root node.  For the array path_info[],
     * path_info[i] is -1 or 1 depending on whether the left or right branch
     * branch was traversed from the (i)th node.  The path_info[] array can
     * then be used for updating balance information.
     */
    stack = t->stack;
    tos = 0;

    /* Attempt to locate the item to be deleted. */
    if ((p = t->root)) {
        /* To locate the minimum, the left branches is repeatedly chosen until
	    * we can explore no further.
         */
        do {
            stack[tos++] = p;
            p = p->left;
        } while (p);
        p = stack[--tos];
    }
    else {
        return NULL;
    }

    /* Right child of p replaces p. */
    if (tos == 0) {
        t->root = p->right;
    }
    else {
        stack[tos - 1]->left = p->right;
        /* stack[tos-1] points to the parent of p. */
    }

    /* Get return value and free space used by node p. */
    return_item = p->item;
    free(p);
    t->n--;

    /* Perform rotations if necessary to rebalance the tree.  This is done
     * by traversing the stack, updating balance information of ancestors,
     * and performing rotations if necessary.
     *
     * Pointer p now points to the node being considered for rebalance.
     */
    while (tos) {
        p = stack[--tos];
        if (p->balance == 0) {
	    /* Balance changes from 0 to 1.  The length of only one
	     * path from p to a leaf has decreased by 1, so the length of the
	     * longest path is unchanged.  Therefore iteration can stop.
	     */
            p->balance++;
            ;
            break; /* Tree is balanced. */
        }
        else {
            p->balance++;

			/* Note that if balance changed from -1 to 0, the length of
			 * the longest path from p to a leaf must have decreased.
			 * Therefore iterations for balance updates will continue.
			 */

            if (p->balance != 0) {
           /* Balance changes from 1 to 2.
            * Now the tree is unbalanced, and rotation must be
            * performed.
            */

           /* The kind of rotation that occurs depends on whether
            * the balance of p's other child (not the child p was reached
            * from) is in the same direction as the balance of p.
            */
                q = p->right; /* p's other child. */
                if (q->balance != -1) {
               /* The balance (p, q) will be either:
                * (2,1), or (2,0)
                */

               /* There is the the following tree structure:
                *  A - right child tree of q.
                *  B - left child tree of q.
                *  C - left child tree of p.
                *      (Deletion occurred in tree C.)
                */

                /* For the rotation:
                *  - tree B replaces node q as the right child of p.
                *  - node p replaces tree B as the left child of q.
                */
                    p->right = q->left;
                    q->left = p;

               /* A child pointer of p's parent changes from p to q.
                * If p was the root, the root node changes.
                */
                    if (tos != 0) {
                        stack[tos - 1]->left = q;
                    }
                    else {
                        t->root = q;
                    }

                    /* Update balance information of nodes p and q. */
                    if (q->balance == 0) {
                        p->balance = 1;
                        q->balance = -1;
                        break; /* Tree is balanced. */
                    }
                    else {
                        p->balance = q->balance = 0;
                    }

               /* Unless q->balance == 0, iterations will continue, since
		        * the length of longest path has decreased.
		        */
                }
                else {
               /* The balance of (p, q) will be (2,-1)
                */

               /* There is the following tree structure:
                *  A - right child tree of q.
                *  B - right child tree of r.
                *  C - left child tree of r.
                *  D - left child tree of p. (Deletion occurred in tree D)
                */

               /* For the rotation:
                *  - tree B replaces node r as the left child of q.
                *  - tree C replaces node q as the right child of p.
                *  - node q replaces tree B as the right child of r.
                *  - node p replaces tree C as the left child of r.
                */
                    r = q->left;
                    q->left = r->right;
                    p->right = r->left;
                    r->right = q;
                    r->left = p;
                    if (r->balance == 1) {
                        p->balance = -1;
                        q->balance = 0;
                    }
                    else if (r->balance == -1) {
                        p->balance = 0;
                        q->balance = 1;
                    }
                    else {
                        p->balance = q->balance = 0;
                    }
                    r->balance = 0;

               /* A child pointer of p's parent changes from p to r.
                * If p was the root, the root node changes.
                */
                    if (tos != 0) {
                        stack[tos - 1]->left = r;
                    }
                    else {
                        t->root = r;
                    }

               /* Continue with further iterations, since the length of
                * longest path has decreased.
                */
                }
            }
        }
    }
    return return_item;
}
