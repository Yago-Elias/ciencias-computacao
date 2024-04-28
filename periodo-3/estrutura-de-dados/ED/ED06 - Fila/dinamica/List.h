typedef struct List List;

List *List_alloc();
void  List_free(List *l);
void  List_insert(List *l, int value);
void  List_insertSorted(List *l, int value);
int   List_remove(List *l, int value);
int   List_getLength(List *l);
void  List_print(List *l);
