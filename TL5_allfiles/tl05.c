// Name: Jingbo Wang

#include "myLib.h"
#include "bill1.h"
#include "bill2.h"
#include "bill3.h"
#include "bill4.h"

u16 *videoBuffer = (u16 *)0x6000000;

void rotateImageAndDraw(int width, int height, const unsigned short *image)
{
    // 1. TODO: Your code here
    // This function takes an image and flips it both horizontally and vertically,
    // and then draws it in the first vertical segment of the GBA screen (with DMA).
    for (int r = 0; r < height; r++)
    {
        DMA[3].src = &image[((height-r)*60)-1]; //color This is always an address!
        DMA[3].dst = &videoBuffer[OFFSET(0+r, 0, width)]; // This is always an address!
        DMA[3].cnt = width/4 | DMA_SOURCE_DECREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }


}
 
void flipVerticallyAndDraw(int width, int height, const unsigned short *image)
{
    // 2. TODO: Your code here
    // This function takes an image and flips it vertically,
    // and then draws it in the second vertical segment of the GBA screen (with DMA).
    for (int r = 0; r < height; r++) {
        // for (int c = 0; c < width; c++) {
        //     u16 image_pixel = image[(height - r - 1) * width + c];
        //     setPixel(row + r, c + col, image_pixel);
        // }
        DMA[3].src = &image[(height-r-1)*60]; //color This is always an address!
        DMA[3].dst = &videoBuffer[OFFSET(r, 60, width)]; // This is always an address!
        DMA[3].cnt = width/4 | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
}

void drawImage3(int row, int col, int width, int height, const unsigned short *image)
{
    // 3. TODO: Your code here
    // This function  will draw an arbitrary sized image
    // onto the screen (with DMA).
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


int main(void)
{
    // 4. TODO: You should probably do something here
    // so that whatever you want to draw actually gets drawn on the screen in Mode 3.
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    
    waitForVblank();

    // 5. TODO: Call your functions appropriately here.
    // You want to draw the Bill images from left to right on the screen.
    rotateImageAndDraw(240, 160, bill1_data);
    flipVerticallyAndDraw(240, 160, bill2_data);
    drawImage3(0, 120, 60, 160, bill3_data);
    drawImage3(0, 180, 60, 160, bill4_data);

    // Wait after drawing
    while (1);
}


void waitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}
