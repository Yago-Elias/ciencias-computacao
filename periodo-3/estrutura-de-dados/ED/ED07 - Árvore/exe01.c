#include <stdio.h>
#include "tree.h"

int evaluate(Tree *tr) {
  if (tr->left == NULL && tr->right == NULL) return tr->value;

  switch (tr->value) {
    case '+': return evaluate(tr->left) + evaluate(tr->right);
    case '-': return evaluate(tr->left) - evaluate(tr->right);
    case '*': return evaluate(tr->left) * evaluate(tr->right);
    case '/': return evaluate(tr->left) / evaluate(tr->right);
  }
}

int main() {
  Tree *tr = Tree_alloc('+',
	          	Tree_alloc('*',
			           Tree_alloc('+',
					      Tree_alloc(3, NULL, NULL),
			                      Tree_alloc(6, NULL, NULL)),
		        	   Tree_alloc('-',
			           	      Tree_alloc(4, NULL, NULL),
				              Tree_alloc(1, NULL, NULL))),
			Tree_alloc(5, NULL, NULL));

  printf("%d\n", evaluate(tr));

  return 0;
}
