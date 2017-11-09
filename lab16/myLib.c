#include "myLib.h"

u16* videoBuffer = (u16*)0x6000000;

void setPixel(int row, int col, u16 color) {
    videoBuffer[row * 240 + col] = color;
}

void waitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}

void drawRedRectangle(int row, int col, int width, int height) {
    unsigned short color = RED;
    for (int r = 0; r < height; r++) {
        DMA[3].src = &color; //color This is always an address!
        DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)]; // This is always an address!
        DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
}

void drawImage(int row, int col, int width, int height, const u16* image) {
    for (int r = 0; r < height; r++) {
        // for (int c = 0; c < width; c++) {
        //     u16 image_pixel = image[r * width + c];
        //     setPixel(row + r, c + col, image_pixel);
        // }
        DMA[3].src = &image[r * width]; //color This is always an address!
        DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)]; // This is always an address!
        DMA[3].cnt = width | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
}

void drawImageFlippedLR(int row, int col, int width, int height, const u16* image) {
    for (int r = 0; r < height; r++) {
        // for (int c = 0; c < width; c++) {
        //     u16 image_pixel = image[r * width + width - c - 1];
        //     setPixel(row + r, c + col, image_pixel);
        // }
        DMA[3].src = &image[((r+1) * width)-1]; //color This is always an address!
        DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)]; // This is always an address!
        DMA[3].cnt = width | DMA_SOURCE_DECREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
}

void drawImageFlippedUD(int row, int col, int width, int height, const u16* image) {
    for (int r = 0; r < height; r++) {
        // for (int c = 0; c < width; c++) {
        //     u16 image_pixel = image[(height - r - 1) * width + c];
        //     setPixel(row + r, c + col, image_pixel);
        // }
        DMA[3].src = &image[(height-r-1)*width]; //color This is always an address!
        DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)]; // This is always an address!
        DMA[3].cnt = width | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
}