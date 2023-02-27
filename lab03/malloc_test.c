#include "malloc.h"
#include <stdio.h>

int main(void) {
    printf("malloc stats test driver\n");
    malloc_stats();
    printf("-------------------------------\n");

    char* ptr = alloc_bytes(512);
    printf("\nAllocated 512 bytes %p\n", ptr);
    malloc_stats();

    ptr = realloc_bytes(ptr, 1024);
    printf("\nReallocated 1024 bytes %p\n", ptr);
    malloc_stats();

    ptr = realloc_bytes(ptr, 128);
    printf("\nReallocated 128 bytes %p\n", ptr);
    malloc_stats();

    ptr = realloc_bytes(ptr, 120 * 1024);
    printf("\nReallocated 1M bytes %p\n", ptr);
    malloc_stats();

    free(ptr);
    printf("\nAfter free %p\n", ptr);
    malloc_stats();
}