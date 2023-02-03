#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    char *ptr = NULL;
    ptr = malloc(256 * sizeof(char));
    if (!ptr) {
        fprintf(stderr, "malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    *(ptr + 100) = 'a';
    *(ptr + 500) = 'b';

    // you may need a larger number to cause the segfault
    *(ptr + 5000000) = 'c';

    printf("Size of char is %ld\n", sizeof(char));
    free(ptr);
}
