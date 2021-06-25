#ifndef IMAGE_H
#define IMAGE_H

#include "data.h"

typedef void (*operation_t)(pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height);

void editPixels(operation_t operation, pixel** input, pixel** output, uint32_t width, uint32_t height);

void makeRed( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height);
void makeBlue( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height);
void makeGreen( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height);
void makeGrey( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height);
void makeBW( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height);
void makeBlur( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height);

#endif