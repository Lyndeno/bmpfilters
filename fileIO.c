#include <stdio.h>
#include "data.h"
#include <stdint.h>

void getFileInfo(FILE *input, struct fileInfo* info) {
    // Read in the values defined in the bitmap header
    fseek(input, 0, SEEK_SET);
    // BMP Header
    fread(&(*info).id1, sizeof(uint8_t), 1, input);
    fread(&(*info).id2, sizeof(uint8_t), 1, input);
    fread(&(*info).size_file, sizeof(uint32_t), 1, input);
    fread(&(*info).unused1, sizeof(uint16_t), 1, input);
    fread(&(*info).unused2, sizeof(uint16_t), 1, input);
    fread(&(*info).pixOffset, sizeof(uint32_t), 1, input);

    // DIB header
    fread(&(*info).dibSize, sizeof(uint32_t), 1, input);
    fread(&(*info).pxWidth, sizeof(uint32_t), 1, input);
    fread(&(*info).pxHeight, sizeof(int32_t), 1, input);
    fread(&(*info).cPlane, sizeof(uint16_t), 1, input);
    fread(&(*info).bitPx, sizeof(uint16_t), 1, input);
    fread(&(*info).pxCompress, sizeof(uint32_t), 1, input);
    fread(&(*info).rawSize, sizeof(uint32_t), 1, input);
    fread(&(*info).dpiH, sizeof(uint32_t), 1, input);
    fread(&(*info).dpiV, sizeof(uint32_t), 1, input);
    fread(&(*info).colors, sizeof(uint32_t), 1, input);
    fread(&(*info).impColors, sizeof(uint32_t), 1, input);
}

void getPixels(FILE* file, pixel** array, uint32_t width, uint32_t height, uint32_t pxOffset, int padding) {
    // Get the amount of padding bytes
    // int padding = (width * (bPerPix / 8)) % 4;

    fseek(file, pxOffset, SEEK_SET); // set the file pointer to where the pixels are
    
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Read in the bytes for blue green and red  int that orde
            fread(&(array[j][i].blue), sizeof(uint8_t), 1, file);
            fread(&(array[j][i].green), sizeof(uint8_t), 1, file);
            fread(&(array[j][i].red), sizeof(uint8_t), 1, file);
        }
        fseek(file, padding, SEEK_CUR); // Skip padding bytes as required
    }
}

void writePixels(FILE* file, pixel** array, uint32_t width, uint32_t height, uint32_t pxOffset, int padding) {
    // Get the amount of padding bytes
    // int padding = (width * (bPerPix / 8)) % 4;

    uint8_t pad[4] = { 0x00, 0x00, 0x00, 0x00 };

    fseek(file, pxOffset, SEEK_SET); // set the file pointer to where the pixels are
    
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Write the blue green and red pixels
            fwrite(&(array[j][i].blue), sizeof(uint8_t), 1, file);
            fwrite(&(array[j][i].green), sizeof(uint8_t), 1, file);
            fwrite(&(array[j][i].red), sizeof(uint8_t), 1, file);
        }
        fwrite(pad, sizeof(uint8_t), padding, file); // sauce some spicy padding bytes into the file as required
    }
}

void writeHeader(FILE* input, FILE* output, uint32_t header_size) {
    // Go to beginning of files
    fseek(input, 0, SEEK_SET);
    fseek(input, 0, SEEK_SET);

    uint8_t byte;

    // Copy number of bytes from input file to output file
    for (uint32_t i = 0; i < header_size; i++) {
        byte = fgetc(input);
        fputc(byte, output);
    }
}

// Calculate the padding required for the bitmap
int getPadding(struct fileInfo* info) {
    int padding = (((*info).rawSize) / (*info).pxHeight) - ((*info).pxWidth * 3);
    return padding;
}