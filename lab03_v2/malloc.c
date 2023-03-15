#include <stdio.h>
#include "malloc.h"

void* alloc_bytes(size_t num_bytes) {
    void* ptr = NULL;
    ptr = malloc(num_bytes);
    if (!ptr) {
        perror("alloc_bytes");
        fprintf(stderr, "malloc(%ld) failed\n", num_bytes);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* realloc_bytes(void* ptr, size_t num_bytes) {
    void* new_ptr = realloc(ptr, num_bytes);
    if (!new_ptr) {
        perror("realloc_bytes");
        fprintf(stderr, "remalloc(%p, %ld) failed\n", ptr, num_bytes);
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}