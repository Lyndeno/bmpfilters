#ifndef FLATTEN_H
#define FLATTEN_H

#include <stdlib.h>
#include "data.h"

typedef struct pixelDict {
	pixel colour;
	size_t total;
	struct pixelDict *next;
} pixelDict;

#endif

void recalcAvg(pixelDict *oldEntry, pixel newColour) {
	(oldEntry->total)++;

	oldEntry->colour.red = ( (oldEntry->colour.red * (oldEntry->total - 1)) + newColour.red) / oldEntry->total; 
	oldEntry->colour.green = ( (oldEntry->colour.green * (oldEntry->total - 1)) + newColour.green) / oldEntry->total; 
	oldEntry->colour.blue = ( (oldEntry->colour.blue * (oldEntry->total - 1)) + newColour.blue) / oldEntry->total;
}
