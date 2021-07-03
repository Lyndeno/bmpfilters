#ifndef FLATTEN_H
#define FLATTEN_H

#include <stdlib.h>
#include <stdbool.h>
#include "data.h"

typedef struct pixelDict {
	pixel colour;
	size_t total;
	struct pixelDict *next;
} pixelDict;

void addPixel(pixelDict *oldEntry, pixel newColour);
bool comparePixels(pixel *a, pixel *b);
pixel *processPixel(pixelDict *dictStart, pixel currentPixel);
void makeFlat(pixel **input, pixel **output, uint32_t width, uint32_t height);
pixel ***allocatePtrs(uint32_t width, uint32_t height);
void freePtrs(pixel ***oldArray, uint32_t width, uint32_t height);

#endif

