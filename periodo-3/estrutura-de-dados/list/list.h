typedef struct List List;

List *List_alloc();
void  List_free(List *lst);
void  List_insert(List *lst, void *value);
void  List_insertSorted(List *lst, void *value, int (*)(void*, void*));
void *List_remove(List *lst, void *value, int (*)(void*, void*));
int   List_getLength(List *lst);
void *List_getValue(List *lst, int index);
int   List_getIndex(List *lst, void *value, int (*)(void*,void*));
void  List_print(List *lst, void (*)(void*));
