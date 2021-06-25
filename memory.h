#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "data.h"

pixel **allocateArray(pixel** array, uint32_t width, uint32_t height);
void freeArray(pixel** array, uint32_t width, uint32_t height);


#endif