#include "malloc.h"

#include <malloc.h>
#include <stdio.h>

int main(void) {
    printf("malloc_stats test driver\n");
    malloc_stats();
    printf("#########################\n");

    char* ptr = alloc_bytes(512);
    printf("\nAllocated 512 bytes %p\n", ptr);
    malloc_stats();
    free(ptr);
}