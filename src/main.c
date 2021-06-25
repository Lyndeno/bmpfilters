#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> // needed for our byte integers
#include <string.h>

#include "data.h"
#include "memory.h"
#include "fileIO.h"
#include "image.h"


void getFileInfo();

int main(void) {

    // define our file names
    char *fileName = malloc(256*sizeof(char));
    char *fileExt = malloc(16*sizeof(char));
    char *inputName = malloc(256*sizeof(char));
    char *outputName = malloc(256*sizeof(char));

    // get filenames from user input
    printf("PLease enter the file you would like to work with: ");
    scanf("%[^.]%s", fileName, fileExt);

    // calculate full file name
    strcat(strcat(inputName, fileName), fileExt);
    

    FILE* inputfile = fopen(inputName, "r+");
    FILE* outputFile;

    // Kill the program if there is an error
    if ( inputfile == NULL ) {
        printf("Oof, the file failed to open, please try again");
        // Free the filenames from memory
        free(inputName); free(fileName); free(fileExt); free(outputName);
        return -1;
    }
    

    // Read the BMP Header
    char id[2];
    fread(id, 1, 2, inputfile);
    if (strcmp(id, "BM") != 0) {
        printf("This ain't no bitmap\n");
        fclose(inputfile);
        return -1;
    } else {
        printf("Nice bitmap\n");
    }
    
    // Get some important file attributes from the header
    struct fileInfo* inputInfo = malloc(sizeof(struct fileInfo));
    getFileInfo(inputfile, inputInfo); // get the header information
    uint32_t pxWidth = (*inputInfo).pxWidth;
    uint32_t pxHeight = (*inputInfo).pxHeight;
    uint32_t pxOffset = (*inputInfo).pixOffset;
    uint16_t bitPx = (*inputInfo).bitPx;
    
    // Define pixel struct arrays
    pixel** inputPixels; // define our pixel array for the input
    pixel** outputPixels; // define our output pixel array, this is what we are going to put our new pixel values in

    // Get the padding value for the pixel arrays
    int padding = getPadding(inputInfo);

    // allocate memory to our pixel array
    inputPixels = allocateArray(inputPixels, pxWidth, pxHeight);
    outputPixels = allocateArray(outputPixels, pxWidth, pxHeight);

    // Read pixels from our input file
    getPixels(inputfile, inputPixels, pxWidth, pxHeight, pxOffset, padding);


    // ===== FILE EDITING SECTION ===== //

    // Extract red channel
    outputName[0] = '\0'; // Empty string
    strcat(strcat(strcat(outputName, fileName), "_red"), fileExt); // Create descriptive filename
    outputFile = fopen(outputName, "w+"); // open the file for writing
    if ( outputFile == NULL ) { printf("Could not open %s for writing", outputName); return -1; } // return an error if something goes wrong
    editPixels(makeRed, inputPixels, outputPixels, pxWidth, pxHeight); // Create the output pixel array
    // Write the information to our new file
    writeHeader(inputfile, outputFile, pxOffset);
    writePixels(outputFile, outputPixels, pxWidth, pxHeight, pxOffset, padding);
    fclose(outputFile); // Close the file

    // Extract green channel
    outputName[0] = '\0'; // Empty string
    strcat(strcat(strcat(outputName, fileName), "_green"), fileExt); // Create descriptive filename
    outputFile = fopen(outputName, "w+"); // open the file for writing
    if ( outputFile == NULL ) { printf("Could not open %s for writing", outputName); return -1; } // return an error if something goes wrong
    editPixels(makeGreen, inputPixels, outputPixels, pxWidth, pxHeight); // Create the output pixel array
    // Write the information to our new file
    writeHeader(inputfile, outputFile, pxOffset);
    writePixels(outputFile, outputPixels, pxWidth, pxHeight, pxOffset, padding);
    fclose(outputFile); // Close the file

    // Extract blue channel
    outputName[0] = '\0'; // Empty string
    strcat(strcat(strcat(outputName, fileName), "_blue"), fileExt); // Create descriptive filename
    outputFile = fopen(outputName, "w+"); // open the file for writing
    if ( outputFile == NULL ) { printf("Could not open %s for writing", outputName); return -1; } // return an error if something goes wrong
    editPixels(makeBlue, inputPixels, outputPixels, pxWidth, pxHeight); // Create the output pixel array
    // Write the information to our new file
    writeHeader(inputfile, outputFile, pxOffset);
    writePixels(outputFile, outputPixels, pxWidth, pxHeight, pxOffset, padding);
    fclose(outputFile); // Close the file

    // GreyScale the image
    outputName[0] = '\0'; // Empty string
    strcat(strcat(strcat(outputName, fileName), "_grey"), fileExt); // Create descriptive filename
    outputFile = fopen(outputName, "w+"); // open the file for writing
    if ( outputFile == NULL ) { printf("Could not open %s for writing", outputName); return -1; } // return an error if something goes wrong
    editPixels(makeGrey, inputPixels, outputPixels, pxWidth, pxHeight); // Create the output pixel array
    // Write the information to our new file
    writeHeader(inputfile, outputFile, pxOffset);
    writePixels(outputFile, outputPixels, pxWidth, pxHeight, pxOffset, padding);
    fclose(outputFile); // Close the file

    // BW the image
    outputName[0] = '\0'; // Empty string
    strcat(strcat(strcat(outputName, fileName), "_bw"), fileExt); // Create descriptive filename
    outputFile = fopen(outputName, "w+"); // open the file for writing
    if ( outputFile == NULL ) { printf("Could not open %s for writing", outputName); return -1; } // return an error if something goes wrong
    editPixels(makeBW, inputPixels, outputPixels, pxWidth, pxHeight); // Create the output pixel array
    // Write the information to our new file
    writeHeader(inputfile, outputFile, pxOffset);
    writePixels(outputFile, outputPixels, pxWidth, pxHeight, pxOffset, padding);
    fclose(outputFile); // Close the file

    // Blur the image
    outputName[0] = '\0'; // Empty string
    strcat(strcat(strcat(outputName, fileName), "_blur"), fileExt); // Create descriptive filename
    outputFile = fopen(outputName, "w+"); // open the file for writing
    if ( outputFile == NULL ) { printf("Could not open %s for writing", outputName); return -1; } // return an error if something goes wrong
    editPixels(makeBlur, inputPixels, outputPixels, pxWidth, pxHeight); // Create the output pixel array
    // Write the information to our new file
    writeHeader(inputfile, outputFile, pxOffset);
    writePixels(outputFile, outputPixels, pxWidth, pxHeight, pxOffset, padding);
    fclose(outputFile); // Close the file

    // ================================ //

    // Free the filenames from memory
    free(inputName); free(fileName); free(fileExt); free(outputName);

    // Free the pixel arrays
    freeArray(inputPixels, pxWidth, pxHeight);
    freeArray(outputPixels, pxWidth, pxHeight);

    // Close the input file
    fclose(inputfile);

    printf("Done processing image; images can be found in the folder of execution\n");
    

}


