#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "list.h"

typedef struct node_type NODE;

struct node_type{
    void *data;
    NODE *next;

};
typedef struct list_type LIST;
struct list_type{
    NODE *head;
    NODE *tail;
    
};


struct list_type *list_create() {
    struct list_type *new_list = malloc(sizeof(struct list_type));
    if (!new_list) {
        perror("list_create");
        exit(EXIT_FAILURE);
    }
    new_list->head = NULL;
    new_list->tail = NULL;

    return new_list;
};

void list_append(struct list_type *list, void *element) {

};