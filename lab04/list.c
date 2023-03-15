#include "list_internal.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

LIST *list_create() {
    //createa a empty list by allocating memory 
    LIST *new_list = malloc(sizeof(LIST));

    if (!new_list) {
        perror("list_create");
        exit(EXIT_FAILURE);
    }
    //head and tail to null
    new_list->head = NULL;
    new_list->tail = NULL;

    return new_list;
}

void list_destroy(LIST *list) {
    if (!list) {
        return;
    }
    //free the memory used by the list
    list_free(list, NULL);
    free(list);
}

void list_free(LIST *list, void (*free_data)(void *data)) {
    if (!list) {
        return;
    }
    //set the current node to the head
    NODE *current_node = list->head;
    while (current_node) {
        NODE *next_node = current_node->next;
        //free the memory used by the nodes
        if (free_data) {
            //free each node data
            free_data(current_node->data);
        }
        free(current_node);
        current_node = next_node;
    }
    list->head = NULL;
    list->tail = NULL;
}

void list_append(LIST *list, void *element) {
    //allocate memory for a new node 
    NODE *new_node = malloc(sizeof(NODE));
    if (!new_node) {
        perror("list_append");
        exit(EXIT_FAILURE);
    }

    //set the new node data to element and set the next to null
    new_node->data = element;
    new_node->next = NULL;
    if (list->head == NULL) {
        //if the head is null, set head, tail to new node
        list->head = new_node;
        list->tail = new_node;
    } else {
        //the head and tail is updated to new node 
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

unsigned int list_insert_at(LIST *list, void *element, unsigned int location) {
    //allocate memory for the node to be inserted at
    NODE *new_node = malloc(sizeof(NODE));
    if (!new_node) {
        perror("list_insert_at");
        exit(EXIT_FAILURE);
    }
    //set its data to the elemetn and set the next nodes before and after the new node to the new node
    new_node->data = element;
    new_node->next = NULL;
    unsigned int i = 0;

    NODE *current_node = list->head;
    NODE *previous_node = NULL;

    while (current_node && i < location) {
        previous_node = current_node;
        current_node = current_node->next;
        i++;
    }
    if (!previous_node) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        previous_node->next = new_node;
        new_node->next = current_node;
    }
    if (!current_node) {
        list->tail = new_node;
    }
    return i;
}

void *list_remove_at(LIST *list, unsigned int location) {
    //removes the node at location and updates the next pointers of node 
    //before and after the removed node to bypass the removed node
    NODE *current_node = list->head;
    NODE *previous_node = NULL;
    unsigned int i = 0;
    while (current_node && i < location) {
        previous_node = current_node;
        current_node = current_node->next;
        i++;
    }
    if (!current_node) {
        return NULL;
    }
    void *data = current_node->data;
    //if the list is empty, the new node is the first node in the list
    if (!previous_node) {
        list->head = current_node->next;
    } else {
        previous_node->next = current_node->next;
    }
    if (!current_node->next) {
        list->tail = previous_node;
    }
    //free the moemory of the current node
    free(current_node);
    return data;
}

void list_remove(LIST *list, void *element) {
    if (list->head == NULL) {
        return;
    }
    //removes the node that have the element
    NODE *curr_node = list->head;
    NODE *prev_node = NULL;
    bool found = false;

    while (curr_node != NULL) {
        //search for the node from head to tail and setting a new next nodes
        if (curr_node->data == element) {
            found = true;
            //if the node is hear or tail, set them up the correct nodes/null
            if (prev_node == NULL) { // element is at the head of the list
                list->head = curr_node->next;
            } else if (curr_node->next == NULL) { // element is at the tail of the list
                prev_node->next = NULL;
                list->tail = prev_node;
            } else {
                prev_node->next = curr_node->next;
            }
            //free the current node
            free(curr_node);
            break;
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    if (!found) {
        // Element not found in the list
        fprintf(stderr, "list_remove: Element not found in list\n");
        exit(EXIT_FAILURE);
    }
}

void *list_to_array(LIST *list) {
    unsigned int num_elements = list_size(list);
    //allocate memory for the array
    void **array = malloc(num_elements * sizeof(void *));
    if (!array) {
        perror("list_to_array");
        exit(EXIT_FAILURE);
    }

    //copy each data from the node to the array
    NODE *curr_node = list->head;
    unsigned int i = 0;
    while (curr_node != NULL) {
        array[i++] = curr_node->data;
        curr_node = curr_node->next;
    }

    return array;
}

unsigned int list_size(LIST *list) {
    unsigned int size = 0;
    NODE *curr_node = list->head;
    //traverse the list and count the nodes
    while (curr_node != NULL) {
        size++;
        curr_node = curr_node->next;
    }

    return size;
}

bool list_is_empty(LIST *list) {
    //return if the list is empty
    return list->head == NULL;
}