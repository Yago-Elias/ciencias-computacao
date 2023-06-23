#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void *value;
    Node *next_node;
};

struct List {
    int length;
    Node *first;
};

List *List_alloc() {
    List *lst = malloc(sizeof(List));

    if (lst) {
        lst->length = 0;
        lst->first = NULL;
    }

    return lst;
}

void List_free(List *lst) {
    Node *node = NULL, *next_node = NULL;

    if (lst) {
        node = lst->first;

        while (node) {
            next_node = node->next_node;
            free(node);
            node = next_node;
        }

        free(lst);
    }
}

void List_insert(List *lst, void *value) {
    Node *new_node = NULL;

    if (lst) {
        new_node = malloc(sizeof(Node));
        new_node->value = value;
        new_node->next_node = NULL;

        if (lst->length > 0)
            new_node->next_node = lst->first;

        lst->first = new_node;
        lst->length++;
    }
}

void List_insertSorted(List *lst, void *value, int (*cmp)(void*, void*)) {
    Node *new_node = NULL, *prev_node = NULL, *node = NULL;

    if (lst) {
        new_node = malloc(sizeof(Node));
        new_node->value = value;
        new_node->next_node = NULL;

        if (lst->length == 0) {
            lst->first = new_node;
        } else {
            node = lst->first;

            while (node)
            {
                if (cmp(new_node->value, node->value) < 0)
                    break;
                prev_node = node;
                node = node->next_node;
            }

            if (prev_node)
                prev_node->next_node = new_node;
            else
                lst->first = new_node;

            new_node->next_node = node;
        }

        lst->length++;
    }
}

void *List_remove(List *lst, void *value, int (*cmp)(void*, void*)) {
    Node *node = NULL, *prev_node = NULL;
    void *value_node;

    if (lst) {
        node = lst->first;

        while(node) {
            if (cmp(node->value, value) == 0) {
                if (prev_node == NULL)
                    lst->first = node->next_node;
                else
                    prev_node->next_node = node->next_node;

                value_node = node->value;
                free(node);
                lst->length--;
                break;
            }

            prev_node = node;
            node = node->next_node;
        }
    }

    return value_node;
}

int List_getLength(List *lst) {
    if (lst)
        return lst->length;

    return 0;
}

void *List_getValue(List *lst, int index) {
    Node *node = NULL;
    int i = 1;

    if (lst) {
        node = lst->first;
        while (node && i++ != index)
            node = node->next_node;
    }

    return node->value;
}

int List_getIndex(List *lst, void *value, int (*cmp)(void*,void*)) {
    Node *node = NULL;
    int index = 1;

    if (lst) {
        node = lst->first;
        while (node) {
            if (cmp(node->value, value) == 0)
                break;
            index++;
            node = node->next_node;
        }
    }

    return index;
}

void List_print(List *lst, void (*print)(void*)) {
    Node *node = NULL;

    if (lst) {
        node = lst->first;

        printf("List(%d): ", lst->length);

        while (node) {
            print(node->value);
            node = node->next_node;
        }

        printf("\n");
    }
}
