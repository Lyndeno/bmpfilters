#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include "data.h"

void getFileInfo(FILE*, struct fileInfo*);
void getPixels(FILE*, pixel**, uint32_t, uint32_t, uint32_t, int);
void writePixels(FILE*, pixel**, uint32_t, uint32_t, uint32_t, int);
void writeHeader(FILE*, FILE*, uint32_t);
int getPadding(struct fileInfo*);

#endif