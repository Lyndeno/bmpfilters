#ifndef DATA_H
#define DATA_H

#include <stdint.h>

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel;

struct fileInfo {
    // BMP Header
    uint8_t id1;
    uint8_t id2;
    uint32_t size_file; // Size of the file
    uint16_t unused1; // App specific
    uint16_t unused2; // App specific
    uint32_t pixOffset; // Offset of pizel Array
    // DIB Header
    uint32_t dibSize; // size of the dib header
    uint32_t pxWidth; // width of image in pixels
    int32_t pxHeight; // pixel height, positive for bottom to top pixel order
    uint16_t cPlane; // number of colour planes
    uint16_t bitPx; // bits per pixel
    uint32_t pxCompress; // pixel compression
    uint32_t rawSize; // size of bitmap data
    uint32_t dpiH; // horizontal px/m
    uint32_t dpiV; // vertical px/m
    uint32_t colors; // # of colors in pallete
    uint32_t impColors; // important colours
};

#endif