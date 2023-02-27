#include <stdlib.h>
#include <stdio.h>

int main(){
    //the amount of int we are allocating
    int size = 1000;

    int* ptr = (int*)malloc(size * sizeof(int));

    //if ptr is empty, we have failed to allocated
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    else {
        //print to show we have allocated
        printf("You have allocated integer array of size %d\n", size);
    }
    //free the allocated memory
    free(ptr);
    return 0;

}
