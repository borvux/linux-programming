#include "malloc.h"
#include <stdio.h>

void* alloc_bytes(size_t num_bytes) {
    void* ptr = NULL;
    ptr = malloc(num_bytes);
    if (!ptr) { //if pointer is equal to  null
        perror("alloc_bytes");
        fprintf(stderr, "malloc(%ld) failed\n", num_bytes); //print it to standard error 
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* realloc_bytes(void* ptr, size_t num_bytes) {
    void* new_ptr = realloc(ptr, num_bytes);
    if (!new_ptr) { //if pointer is equal to  null
        perror("realloc_bytes");
        fprintf(stderr, "realloc(%p, %ld) failed\n", new_ptr, num_bytes); //print it to standard error 
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}