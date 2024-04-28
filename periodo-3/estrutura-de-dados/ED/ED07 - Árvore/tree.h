typedef struct Tree Tree;

struct Tree {
  int value;
  Tree *left;
  Tree *right;
};

Tree *Tree_alloc(int value, Tree *left, Tree *right);
void Tree_free(Tree *tr);
void Tree_print(Tree *tr);
