#include "image.h"

// Dimensions of square to blur around, odd values will probably work better
// 7x7 is the required dimensions for this assignment
#define BLUR_DIMENSION_X 7
#define BLUR_DIMENSION_Y 7

// This function loops through all pixels executing the desired function
void editPixels(operation_t operation, pixel** input, pixel** output, uint32_t width, uint32_t height) {
    for ( int i = 0; i < height; i++) { // iterate through heght
        for (int j = 0; j < width; j++) { // iterate through width
            operation(input, output, j, i, width, height);
        }
    }
}

// This function extracts the red channel from the image
void makeRed( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height) {
    output[x][y].red = input[x][y].red; // set the red channel of the output to the red channel of the input
    output[x][y].blue = output[x][y].green = 0; // zero out unwanted channels
}

// This function extracts the blue channel from the image
void makeBlue( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height) {
    output[x][y].blue = input[x][y].blue; // set the blue channel of the output to the blue channel of the input
    output[x][y].red = output[x][y].green = 0; // zero out unwanted channels
}

// This function extracts the green channel from the image
void makeGreen( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height) {
    output[x][y].green = input[x][y].green; // set the green channel of the output to the green channel of the input
    output[x][y].blue = output[x][y].red = 0; // zero out unwanted channels
}

// This function creates a greyscale version of the image
void makeGrey( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height) {
    uint8_t avg = (input[x][y].red + input[x][y].green + input[x][y].blue) / 3; // Get the average value of the colour channels
    output[x][y].red = output[x][y].green = output[x][y].blue = avg; // set each channel to this value to make a shade of grey 
}

// This function calculates the average of the all the colours and sets the pixel to either black or white depending on the average
void makeBW( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height) {
    uint8_t val;
    uint8_t avg = (input[x][y].red + input[x][y].green + input[x][y].blue) / 3; // Get the average value of the colour channels
    if (avg > 127) {
        val = 255; // set pixel colour to white
    } else { val = 0; } // set pixel colour to black
    output[x][y].red = output[x][y].green = output[x][y].blue = val; // set each channel to either black or white
}

void makeBlur( pixel** input, pixel** output, int x, int y, uint32_t width, uint32_t height) {
    // Set the bounds for our calculations
    int x_offset = (BLUR_DIMENSION_X - 1) / 2;
    int y_offset = (BLUR_DIMENSION_Y - 1) / 2;

    int h_low_bound = x - x_offset;
    int h_high_bound = x + x_offset;
    int v_low_bound = y - y_offset;
    int v_high_bound = y + y_offset;

    int pixCount = 0;

    int r_tot = 0;
    int g_tot = 0;
    int b_tot = 0;

    uint8_t r_avg;
    uint8_t g_avg;
    uint8_t b_avg;

    // Check if our calc bounds step out of the bounds of the image, if so, adjust accordingly
    if (h_low_bound < 0) { h_low_bound = 0;}
    if (h_high_bound >= width) { h_high_bound = width - 1; }
    if (v_low_bound < 0 ) { v_low_bound = 0; }
    if (v_high_bound >= height ) { v_high_bound = height - 1; }

    for ( int i = h_low_bound; i <= h_high_bound; i++) { // iterate through the width of the region
        for ( int j = v_low_bound; j <= v_high_bound; j++ ) { // iterate through the height of the region
            // Add the colour channels to our total
            r_tot += input[i][j].red;
            g_tot += input[i][j].green;
            b_tot += input[i][j].blue;

            // Increase the pixel count
            pixCount++;
        }
    }

    // Get the averages for each colour channel
    r_avg = r_tot / pixCount;
    g_avg = g_tot / pixCount;
    b_avg = b_tot / pixCount;

    // Write these colour channels to the output
    output[x][y].red = r_avg;
    output[x][y].green = g_avg;
    output[x][y].blue = b_avg;

}