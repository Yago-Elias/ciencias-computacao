/*** File RB.c - Red-Black Tree ***/
/*
 *   Shane Saunders
 */
#include <stdlib.h>
#include "RB.h"

/* Prototypes for functions only visible within this file. */
RB_node *RB_restructure(RB *t, int tos, RB_node *x, RB_node *y, RB_node *z);
RB_node *RB_restructure2(RB *t, int tos, RB_node *x, RB_node *y, RB_node *z);

/* RB_alloc() - Allocates space for a red-black tree and returns a pointer
 * to it.  The function compar compares they keys of two items, and returns a
 * negative, zero, or positive integer depending on whether the first item is
 * less than, equal to, or greater than the second.
 */
RB *RB_alloc(int (*compar)(const void *, const void *)) {
	RB *t;

	t = malloc(sizeof(RB));
	t->root = NULL;
	t->compar = compar;
	t->stack = malloc(RB_STACK_SIZE * sizeof(RB_node *));
	t->n = 0;

	return t;
}

/* RB_free() - Frees space used by the red-black tree pointed to by t. */
void RB_free(RB *t) {
	RB_node *p, **stack;
	int tos;

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
		free(stack);
	}

	free(t);
}

/* RB_insert() - Inserts an item into the red-black tree pointed to by t,
 * according the the value its key.  The key of an item in the red-black
 * tree must be unique among items in the tree.  If an item with the same key
 * already exists in the tree, a pointer to that item is returned.  Otherwise,
 * NULL is returned, indicating insertion was successful.
 */
void *RB_insert(RB *t, void *item) {
	RB_node *x, *p, *q, *m, **attach_x;
	int (*compar)(const void *, const void *);
	int cmp_result;
	RB_colour col;
	RB_node **stack;
	int tos;

	tos = 0;
	if ((p = t->root)) {
		compar = t->compar;
		stack = t->stack;

		/* Repeatedly explore either the left branch or the right branch
		 * depending on the value of the key, until an empty branch is chosen.
		 */
		for (;;) {
			stack[tos++] = p;
			cmp_result = compar(item, p->item);
			if (cmp_result < 0) {
				p = p->left;
				if (!p) {
					p = stack[--tos];
					attach_x = &p->left;
					break;
				}
			}
			else if (cmp_result > 0) {
				p = p->right;
				if (!p) {
					p = stack[--tos];
					attach_x = &p->right;
					break;
				}
			}
			else {
				return p->item;
			}
		}
		col = Red;
	}
	else {
		attach_x = &t->root;
		col = Black;
	}

	x = malloc(sizeof(RB_node));
	x->left = x->right = NULL;
	x->item = item;
	x->colour = col;

	*attach_x = x;
	t->n++;

	/* Restructuring or recolouring will be needed if node x and its parent, p,
	 * are both red.
	 */
	if (tos > 0)
		while (p->colour == Red) { /* Double red problem. */

			/* Obtain a pointer to p's parent, m, and sibling, q. */
			m = stack[--tos];
			q = p == m->left ? m->right : m->left;

			/* Determine whether restructuring or recolouring is needed. */
			if (!q || q->colour == Black) {
				/* Sibling is black.  ==>  Perform restructuring. */

				/* Restructure according to the left to right order, of nodes
				 * m, p, and x.
				 */
				m = RB_restructure(t, tos, m, p, x);
				m->colour = Black;
				m->left->colour = m->right->colour = Red;

				/* Restructuring eliminates the double red problem. */
				break;
			}
			/* else */

			/* Sibling is also red.  ==>  Perform recolouring. */
			p->colour = Black;
			q->colour = Black;

			if (tos == 0)
				break; /* The root node always remains black. */

			m->colour = Red;

			/* Continue, checking colouring higher up. */
			x = m;
			p = stack[--tos];
		}

	return NULL;
}

/* RB_find() - Find an item in the red-black tree with the same key as the
 * item pointed to by `key_item'.  Returns a pointer to the item found, or NULL
 * if no item was found.
 */
void *RB_find(RB *t, void *key_item) {
	RB_node *p, *next_p;
	int (*compar)(const void *, const void *);
	int cmp_result;

	compar = t->compar;

	if ((next_p = t->root)) {
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

/* RB_find_min() - Returns a pointer to the minimum item in the red-black
 * tree pointed to by t.  If there are no items in the tree a NULL pointer is
 * returned.
 */
void *RB_find_min(RB *t) {
	RB_node *p, *next_p;

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

/* RB_delete() - Delete an item in the red-black tree with the same key as
 * the item pointed to by `key_item'.  Returns a pointer to the deleted item,
 * and NULL if no item was found.
 */
void *RB_delete(RB *t, void *key_item) {
	RB_node *p, *r, *x, *y, *z, *b, *new_y;
	RB_node *m;
	RB_colour remove_col;
	void *return_item;
	int (*compar)(const void *, const void *);
	int cmp_result;
	RB_node **stack;
	int i, tos;

	/* Attempt to locate the item to be deleted. */
	if ((p = t->root)) {
		compar = t->compar;
		stack = t->stack;
		tos = 0;

		for (;;) {
			stack[tos++] = p;
			cmp_result = compar(key_item, p->item);
			if (cmp_result < 0) {
				p = p->left;
			}
			else if (cmp_result > 0) {
				p = p->right;
			}
			else {
				/* Item found. */
				break;
			}
			if (!p)
				return NULL;
		}
	}
	else {
		return NULL;
	}

	/* p points to the node to be deleted, and is currently on the top of the
	 * stack.
	 */
	if (!p->left) {
		tos--; /* Adjust tos to remove p. */
		/* Right child replaces p. */
		if (tos == 0) {
			r = t->root = p->right;
			x = y = NULL;
		}
		else {
			x = stack[--tos];
			if (p == x->left) {
				r = x->left = p->right;
				y = x->right;
			}
			else {
				r = x->right = p->right;
				y = x->left;
			}
		}
		remove_col = p->colour;
	}
	else if (!p->right) {
		tos--; /* Adjust tos to remove p. */
		/* Left child replaces p. */
		if (tos == 0) {
			r = t->root = p->left;
			x = y = NULL;
		}
		else {
			x = stack[--tos];
			if (p == x->left) {
				r = x->left = p->left;
				y = x->right;
			}
			else {
				r = x->right = p->left;
				y = x->left;
			}
		}
		remove_col = p->colour;
	}
	else {
		/* Save p's stack position. */
		i = tos - 1;

		/* Minimum child, m, in the right subtree replaces p. */
		m = p->right;
		do {
			stack[tos++] = m;
			m = m->left;
		} while (m);
		m = stack[--tos];

		/* Update either the left or right child pointers of p's parent. */
		if (i == 0) {
			t->root = m;
		}
		else {
			x = stack[i - 1]; /* p's parent. */
			if (p == x->left) {
				x->left = m;
			}
			else {
				x->right = m;
			}
		}

		/* Update the tree part m is removed from, and assign m the child
		 * pointers of p (only if m is not the right child of p).
		 */
		stack[i] = m; /* Node m replaces node p on the stack. */
		x = stack[--tos];
		r = m->right;
		if (tos != i) { /* x is equal to the parent of m. */
			y = x->right;
			x->left = r;
			m->right = p->right;
		}
		else { /* m was the right child of p, and x is equal to m. */
			y = p->left;
		}
		m->left = p->left;

		/* We treat node m as the node which has been removed. */
		remove_col = m->colour;
		m->colour = p->colour;
	}

	/* Get return value and free the space used by node p. */
	return_item = p->item;
	free(p);

	t->n--;

	/* The pointers x, y, and r point to nodes which may be involved in
	 * restructuring and recolouring.
	 *  x - the parent of the removed node.
	 *  y - the sibling of the removed node.
	 *  r - the node which replaced the removed node.
	 * From the above code, the next entry off the stack will be the parent of
	 * node x.
	 */

	/* The number of black nodes on paths to all external nodes (NULL child
	 * pointers) must remain the same for all paths.  Restructuring or
	 * recolouring of nodes may be necessary to enforce this.
	 */
	if (remove_col == Black) {
		/* Removal of a black node requires some adjustment. */

		if (!r || r->colour == Black) {
			/* A black node replaced the deleted black node.  Note that
			 * external nodes (NULL child pointers) are always black, so
			 * if r is NULL it is treated as a black node.
			 */

			/* This causes a double-black problem, since node r would need to
			 * be coloured double-black in order for the black colour on
			 * paths through r to remain the same as for other paths.
			 */

			/* If r is the root node, the double-black colour is not necessary
			 * to maintain the colour balance.  Otherwise, some adjustment of
			 * nearby nodes is needed in order to eliminate the double-black
			 * problem.  NOTE:  x points to the parent of r.
			 */
			if (x)
				for (;;) {

					/* There are three adjustment cases:
					 *  1.  r's sibling, y, is black and has a red child, z.
					 *  2.  r's sibling, y, is black and has two black children.
					 *  3.  r's sibling, y, is red.
					 */
					if (y->colour == Black) {

						/* Note the conditional evaluation for assigning z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red)) {
							/* Case 1:  perform a restructuring of nodes x, y, and
							 * z.
							 */

							b = RB_restructure(t, tos, x, y, z);
							b->colour = x->colour;
							b->left->colour = b->right->colour = Black;

							break;
						}
						else {
							/* Case 2:  recolour node y red. */

							y->colour = Red;

							if (x->colour == Red) {
								x->colour = Black;
								break;
							}
							/* else */

							if (tos == 0)
								break; /* Root level reached. */
									   /* else */

							r = x;
							x = stack[--tos]; /* x <- parent of x. */
							y = x->left == r ? x->right : x->left;
						}
					}
					else {
						/* Case 3:  Restructure nodes x, y, and z, where:
						 *  - If node y is the left child of x, then z is the left
						 *    child of y.  Otherwise z is the right child of y.
						 */
						if (x->left == y) {
							new_y = y->right;
							z = y->left;
						}
						else {
							new_y = y->left;
							z = y->right;
						}

						RB_restructure(t, tos, x, y, z);
						y->colour = Black;
						x->colour = Red;

						/* Since x has moved down a place in the tree, and y is the
						 * new the parent of x, the stack must be adjusted so that
						 * the parent of x is correctly identified in the next call
						 * to RB_restructure().
						 */
						stack[tos++] = y;

						/* After restructuring, node r has a black sibling, new_y,
						 * so either case 1 or case 2 applies.  If case 2 applies
						 * the double-black problem does not reappear.
						 */
						y = new_y;

						/* Note the conditional evaluation for assigning z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red)) {
							/* Case 1:  perform a restructuring of nodes x, y, and
							 * z.
							 */

							b = RB_restructure(t, tos, x, y, z);
							b->colour = Red; /* Since node x was red. */
							b->left->colour = b->right->colour = Black;
						}
						else {
							/* Case 2:  recolour node y red. */

							/* Note that node y is black and node x is red. */

							y->colour = Red;
							x->colour = Black;
						}

						break;
					}
				}
		}
		else {
			/* A red node replaced the deleted black node. */

			/* In this case we can simply colour the red node black. */
			r->colour = Black;
		}
	}

	return return_item;
}

/* RB_delete_min() - Deletes the item with the smallest key from the binary
 * search tree pointed to by t.  Returns a pointer to the deleted item.
 * Returns a NULL pointer if there are no items in the tree.
 */
void *RB_delete_min(RB *t) {
	RB_node *p, *r, *x, *y, *z, *b, *new_y;
	RB_colour remove_col;
	void *return_item;
	RB_node **stack;
	int tos;

	/* Attempt to locate the item to be deleted. */
	if ((p = t->root)) {
		stack = t->stack;
		tos = 0;

		/* To locate the minimum, the left branches is repeatedly chosen until
		 * we can explore no further.
		 */
		do {
			stack[tos++] = p;
			p = p->left;
		} while (p);
		p = stack[--tos]; /* Node to be deleted. */
	}
	else {
		return NULL;
	}

	/* Right child replaces p. */
	if (tos == 0) {
		r = t->root = p->right;
		x = y = NULL;
	}
	else {
		x = stack[--tos];
		r = x->left = p->right;
		y = x->right;
	}
	remove_col = p->colour;

	/* Get return value and free space used by node p. */
	return_item = p->item;
	free(p);

	t->n--;

	/* The pointers x, y, and r point to nodes which may be involved in
	 * restructuring and recolouring.
	 *  x - the parent of the removed node.
	 *  y - the sibling of the removed node.
	 *  r - the node which replaced the removed node.
	 */

	/* The number of black nodes on paths to all external nodes (NULL child
	 * pointers) must remain the same for all paths.  Restructuring or
	 * recolouring of nodes may be necessary to enforce this.
	 */
	if (remove_col == Black) {
		/* Removal of a black node requires some adjustment. */

		if (!r || r->colour == Black) {
			/* A black node replaced the deleted black node.  Note that
			 * external nodes (NULL child pointers) are always black, so
			 * if r is NULL it is treated as a black node.
			 */

			/* This causes a double-black problem, since node r would need to
			 * be coloured double-black in order for the black colour on
			 * paths through r to remain the same as for other paths.
			 */

			/* If r is the root node, the double-black colour is not necessary
			 * to maintain the colour balance.  Otherwise, some adjustment of
			 * nearby nodes is needed in order to eliminate the double-black
			 * problem.  NOTE:  x points to the parent of r.
			 */
			if (x)
				for (;;) {

					/* There are three adjustment cases:
					 *  1.  r's sibling, y, is black and has a red child, z.
					 *  2.  r's sibling, y, is black and has two black children.
					 *  3.  r's sibling, y, is red.
					 */
					if (y->colour == Black) {

						/* Note the conditional evaluation for assigning z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red)) {
							/* Case 1:  perform a restructuring of nodes x, y, and
							 * z.
							 */

							b = RB_restructure2(t, tos, x, y, z);
							b->colour = x->colour;
							b->left->colour = b->right->colour = Black;

							break;
						}
						else {
							/* Case 2:  recolour node y red. */

							y->colour = Red;

							if (x->colour == Red) {
								x->colour = Black;
								break;
							}
							/* else */

							if (tos == 0)
								break; /* Root level reached. */
									   /* else */

							r = x;
							x = stack[--tos]; /* x <- parent of x. */
							y = x->left == r ? x->right : x->left;
						}
					}
					else {
						/* Case 3:  Restructure nodes x, y, and z, where:
						 *  - If node y is the left child of x, then z is the left
						 *    child of y.  Otherwise z is the right child of y.
						 */
						if (x->left == y) {
							new_y = y->right;
							z = y->left;
						}
						else {
							new_y = y->left;
							z = y->right;
						}

						RB_restructure2(t, tos, x, y, z);
						y->colour = Black;
						x->colour = Red;

						/* Since x has moved down a place in the tree, and y is the
						 * new the parent of x, the stack must be adjusted so that
						 * the parent of x is correctly identified in the next call
						 * to RB_restructure().
						 */
						stack[tos++] = y;

						/* After restructuring, node r has a black sibling, new_y,
						 * so either case 1 or case 2 applies.  If case 2 applies
						 * the double-black problem does not reappear.
						 * Note:  x still points to the parent of r, but y must be
						 * updated to point to r's new sibling, new_y.
						 */
						y = new_y;

						/* Note the conditional evaluation for assigning z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red)) {
							/* Case 1:  perform a restructuring of nodes x, y, and
							 * z.
							 */

							b = RB_restructure2(t, tos, x, y, z);
							b->colour = Red; /* Since node x was red. */
							b->left->colour = b->right->colour = Black;
						}
						else {
							/* Case 2:  recolour node y red. */

							/* Note that node y is black and node x is red. */

							y->colour = Red;
							x->colour = Black;
						}

						break;
					}
				}
		}
		else {
			/* A red node replaced the deleted black node. */

			/* In this case we can simply colour the red node black. */
			r->colour = Black;
		}
	}

	return return_item;
}

/*** Restructuring functions. ***/

/* RB_restructure() - General restructuring function - checks for all
 * restructuring cases.
 */
RB_node *RB_restructure(RB *t, int tos, RB_node *x,
						RB_node *y, RB_node *z) {
	RB_node *parent, *mid_node;

	if (y == x->left) {
		if (z == y->left) { /* in-order:  z, y, x */
			mid_node = y;
			y->left = z;
			x->left = y->right;
			y->right = x;
		}
		else { /* in-order:  y, z, x */
			mid_node = z;
			y->right = z->left;
			z->left = y;
			x->left = z->right;
			z->right = x;
		}
	}
	else {
		if (z == y->left) { /* in-order:  x, z, y */
			mid_node = z;
			x->right = z->left;
			z->left = x;
			y->left = z->right;
			z->right = y;
		}
		else { /* in-order:  x, y, z */
			mid_node = y;
			x->right = y->left;
			y->left = x;
			y->right = z;
		}
	}

	if (tos != 0) {
		parent = t->stack[tos - 1];
		if (x == parent->left) {
			parent->left = mid_node;
		}
		else {
			parent->right = mid_node;
		}
	}
	else {
		t->root = mid_node;
	}

	return mid_node;
}

/* RB_restructure2() - Restructuring function used by delete_min.  There
 * are fewer restructuring cases to consider since it is known that y will
 * always be the right child of x.
 */
RB_node *RB_restructure2(RB *t, int tos, RB_node *x,
						 RB_node *y, RB_node *z) {
	RB_node *parent, *mid_node;

	if (z == y->left) { /* in-order:  x, z, y */
		mid_node = z;
		x->right = z->left;
		z->left = x;
		y->left = z->right;
		z->right = y;
	}
	else { /* in-order:  x, y, z */
		mid_node = y;
		x->right = y->left;
		y->left = x;
		y->right = z;
	}

	if (tos != 0) {
		parent = t->stack[tos - 1];
		if (x == parent->left) {
			parent->left = mid_node;
		}
		else {
			parent->right = mid_node;
		}
	}
	else {
		t->root = mid_node;
	}

	return mid_node;
}
