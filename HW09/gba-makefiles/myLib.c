#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

int collide(OBJECT obj1, OBJECT obj2) 
{
	if (obj1.row >= obj2.row-obj1.size && obj1.row <= obj2.row+obj2.size && obj1.col >= obj2.col-obj1.size && obj1.col <= obj2.col+obj2.size)
	{
		//top edge
		return 1;
	}
	return 0;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r=0; r<height; r++)
	{
		DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
        DMA[3].cnt = (width) | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;
	
	}
}

void delay(int n)
{
	volatile int size = 0;
	for(int i=0; i<n*4000; i++)
	{
		size = size + 1;
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void drawImage(int row, int col, int width, int height, const u16* image) {
    for (int r = 0; r < height; r++) {
        DMA[3].src = &image[r * width];
        DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
        DMA[3].cnt = width | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
}