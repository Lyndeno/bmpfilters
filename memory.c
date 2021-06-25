#include "memory.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>

static int bytesAllocated = 0;


// This function allocates memory for a 2d pixel array
pixel **allocateArray(pixel** array, uint32_t width, uint32_t height) {
    // allocate the array of pointers spanning the width
    array = malloc(width*sizeof(*array));
    bytesAllocated += width*sizeof(*array);
    // allocate a height column for each X value spanning the width
    for (int i = 0; i < width; i++) {
        array[i] = malloc(height*sizeof(pixel));
        bytesAllocated += height*sizeof(pixel);
    }


    // Print the current amount of memory allocated to the program
    printf("Current amount of memory allocated: %d bytes\n\n", bytesAllocated);

    // Once all the memory is allocated, return the pointer to this space
    return array;
}

// This function allocates memory for a 2d pixel array
void freeArray(pixel** array, uint32_t width, uint32_t height) {
    // Free the height pointer from memory
    for (int i = 0; i < width; i++) {
        free(array[i]);
        bytesAllocated -= height*sizeof(pixel);
    }
    // Free the width pointer from memory
    free(array);
    bytesAllocated -= width*sizeof(*array);


    // Print the current amount of memory allocated to the program
    printf("Current amount of memory allocated: %d bytes\n\n", bytesAllocated);

}
