#include "myLib.h"
#include "text.h"

void drawChar(int row, int col, char ch, unsigned short color)
{
	for(int r=0; r< 8; r++)
	{
		for(int c=0; c<6; c++)
		{
			if (fontdata_6x8[OFFSET(r, c, 6) + ch*48] == 1)
			{
				DMA[3].src = &color;
        		DMA[3].dst = &videoBuffer[OFFSET(row+r, col+c, 240)];
        		DMA[3].cnt = 1 | DMA_SOURCE_FIXED | DMA_DESTINATION_FIXED | DMA_ON;
			}
		}
	}
}

void drawString(int row, int col, char str[], unsigned short color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col += 6;
		
	}
}