#include <stdio.h>

typedef unsigned int u32;
typedef unsigned short u16;


#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3

#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

#define SCREENHEIGHT 149

#define BG2_ENABLE (1<<10)
#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define RED COLOR(31, 0, 0)
#define GREEN COLOR(0, 31, 0)
#define BLUE COLOR(0,0,31)
#define YELLOW COLOR(31,31,0)
#define WHITE COLOR(31,31,31)
#define BLACK 0
#define DKGRAY COLOR(15, 15, 15)


#define OFFSET(row, col, rowlen)  ((row)*(rowlen)+(col))


// Buttons

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130

/* DMA */

#define REG_DMA0SAD         *(volatile u32*)0x40000B0 		// source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(volatile u32*)0x40000BC 		// source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(volatile u32*)0x40000C8 		// source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(volatile u32*)0x40000D4 		// source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register


typedef struct
{
	const volatile void *src;
	volatile void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)


#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)


extern const unsigned char fontdata_6x8[12288];
unsigned short *videoBuffer = (unsigned short *)0x6000000;

// Prototypes
void setPixel(int row, int col, unsigned short color);
void drawRect(int row, int col, int height, int width, unsigned short color);
void delay(int n);
void waitForVblank();
void drawChar(int row, int col, char ch, unsigned short color);
void drawString(int row, int col, char str[], unsigned short color);


int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	//* (  19320 +videoBuffer   )= 32767;
	//videoBuffer[OFFSET(80, 120, 240)] = WHITE;
	int row = 80;
	int col = 120;
	int rdel = 1;
	int cdel = 1;
	int size = 5;
	int oldrow = row;
	int oldcol = col;
	int oldsize = size;

	u16 bgcolor = DKGRAY;
	//drawChar(150, 5, 'A', YELLOW);
	/*
	char ch = 0;
	for(int r=0; r<16; r++)
	{
		for(int c=0; c<16; c++)
		{
			drawChar(r*9, c*9, ch++, YELLOW);
		}
	}
	while(1);
	*/
	//char buffer[] = "Dear Mom, Send Money!";
	//char *message = "Dear Mom, Send Money!";
	int score = 0;
	//drawString(150, 5, "Dear Mom, Send Money!", YELLOW);
	//while(1);
	char buffer[41];
	REG_DMA3SAD = (u32)&bgcolor;
	REG_DMA3DAD = (u32)videoBuffer;
	REG_DMA3CNT = (160*240) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
	while(1)
	{
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			size++;
			if(size>150)
			{
				size = 150;
			}
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			size--;
			if(size<3)
			{
				size = 3;
			}
		}
		row = row + rdel;
		col = col + cdel;
		
		if(row < 0)
		{
			row =0;
			rdel = -rdel;
			score++;
		}
		if(row > SCREENHEIGHT-size+1)
		{
			row = SCREENHEIGHT-size+1;
			rdel = -rdel;
		}
		if(col < 0)
		{
			col = 0;
			cdel = -cdel;
		}
		if(col > 239-size+1)
		{
			col = 239-size+1;
			cdel = -cdel;
		}
		waitForVblank();
		drawRect(150, 5, 10, 60, bgcolor);
		sprintf(buffer, "Score: %d", score);
		drawString(150, 5, buffer, YELLOW);
		drawRect(oldrow, oldcol, oldsize, oldsize, bgcolor);
		drawRect(row, col, size, size, YELLOW);
		oldcol = col;
		oldrow = row;
		oldsize = size;
		
		
	}

}

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}
#if 0
void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r=0; r<height; r++)
	{
		for(int c=0; c<width; c++)
		{
			setPixel(row+r, col+c, color);
		}
	}
}
#endif

//#if 0
void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r=0; r<height; r++)
	{
		REG_DMA3SAD = (u32)&color;
		REG_DMA3DAD = (u32)&videoBuffer[OFFSET(row+r, col, 240)];
		//REG_DMA3DAD = (u32)(videoBuffer + OFFSET(row+r, col, 240) );

		REG_DMA3CNT = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
		/*
		for(int c=0; c<width; c++)
		{
			setPixel(row+r, col+c, color);
		}
		*/
	}
}
//#endif

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

void drawChar(int row, int col, char ch, unsigned short color)
{
	for(int r=0; r< 8; r++)
	{
		for(int c=0; c<6; c++)
		{
			if (fontdata_6x8[OFFSET(r, c, 6) + ch*48] == 1)
			{
				setPixel(row+r, col+c, color);
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

















