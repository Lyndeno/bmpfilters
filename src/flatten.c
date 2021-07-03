#include "flatten.h"
#include <stdlib.h>
#include <stdbool.h>

#define RED_DIST 15
#define GREEN_DIST 15
#define BLUE_DIST 15


void addPixel(pixelDict *oldEntry, pixel newColour) {
	(oldEntry->total)++;

	oldEntry->colour.red = ( (oldEntry->colour.red * (oldEntry->total - 1)) + newColour.red) / oldEntry->total; 
	oldEntry->colour.green = ( (oldEntry->colour.green * (oldEntry->total - 1)) + newColour.green) / oldEntry->total; 
	oldEntry->colour.blue = ( (oldEntry->colour.blue * (oldEntry->total - 1)) + newColour.blue) / oldEntry->total;
}

pixelDict *initPixelDict() {
	pixelDict *newEntry = malloc(sizeof(pixelDict));

	newEntry->next = NULL;
	newEntry->total = 0;
	return newEntry;
}

void makeFlat(pixel **input, pixel **output, uint32_t width, uint32_t height) {
	pixelDict *firstPixel = initPixelDict();
	pixel ***intermitPixels = allocatePtrs(width, height);

	for (uint32_t x = 0; x < width; x++) {
		for (uint32_t y = 0; y < height; y++) {
			intermitPixels[x][y] = processPixel(firstPixel, input[x][y]);
		}
	}
	for (uint32_t x = 0; x < width; x++) {
		for (uint32_t y = 0; y < height; y++) {
			output[x][y] = *(intermitPixels[x][y]);
		}
	}
	freePtrs(intermitPixels, width, height);
} 

pixel ***allocatePtrs(uint32_t width, uint32_t height) {
	pixel ***newArray = malloc(width*sizeof(pixel**));

	for (uint32_t i = 0; i < width; i++) {
		newArray[i] = malloc(height*sizeof(pixel*));
	}
	return newArray;
}

void freePtrs(pixel ***oldArray, uint32_t width, uint32_t height) {
	for (uint32_t i = 0; i < width; i++) {
		free(oldArray[i]);
	}
	free(oldArray);
}

/*
 * Take pixel and compare it to the list of colour averages
 */
pixel *processPixel(pixelDict *dictStart, pixel currentPixel) {
	pixelDict *currentDict = dictStart;

	if ( currentDict->total != 0 ) {
		while(true) {
			if ( comparePixels(&(currentDict->colour), &currentPixel) ) {
				addPixel(currentDict, currentPixel);
				break;
			} else if (currentDict->next == NULL) {
				currentDict->next = initPixelDict();
				currentDict = currentDict->next;
				currentDict->colour = currentPixel;
				(currentDict->total)++;
				break;
			} else {
				currentDict = currentDict->next;
			}
		}
	} else {
		currentDict->colour = currentPixel;
		(currentDict->total)++;
	}
	return &(currentDict->colour);
}

/*
 * Return true if each colour is within defined distance
 */
bool comparePixels(pixel *a, pixel *b) {
	bool red = abs( (int)(a->red) - (int)(b->red) ) <= RED_DIST;
	bool green = abs( (int)(a->green) - (int)(b->green) ) <= GREEN_DIST;
	bool blue = abs( (int)(a->blue) - (int)(b->blue) ) <= BLUE_DIST;

	return (red & green & blue);
}
