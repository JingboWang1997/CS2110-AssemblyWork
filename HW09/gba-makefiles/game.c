#include <stdio.h>

typedef unsigned int u32;

#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3

#define SCANLINECOUNTER *(volatile unsigned short *) 0x4000006

#define SCREENHEIGHT 149

#define BG2_ENABLE (1<<10)
#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define YELLOW COLOR(31, 31,0)
#define OFFSET(r, c, rowlen) ((r)*(rowlen)+(c))
#define BLACK 0
#define LTGRAY COLOR(25, 25, 25)



extern const unsigned char fontdata_6x8[12288];

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


typedef struct
{
	int row;
	int col;
	int size;
	int oldrow;
	int oldcol;
} PLAYER;

typedef struct
{
	int row;
	int col;
	int size;
	int oldrow;
	int oldcol;
	int rdel;
	int cdel;
} ENEMY;

unsigned short *videoBuffer = (unsigned short *)0x6000000;

// Prototypes
void setPixel(int row, int col, unsigned short color);
void drawRect(int row, int col, int height, int width, unsigned short color);
void delay(int n);
void waitForVblank();
void drawChar(int row, int col, char ch, unsigned short color);
void drawString(int row, int col, char str[], unsigned short color);
int hit(PLAYER player, ENEMY enemy);

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	
	PLAYER player;
	player.row = 5;
	player.col = 5;
	player.size = 5;
	player.oldrow = 5;
	player.oldcol = 5;

	ENEMY enemy1;
	enemy1.row = 5;
	enemy1.col = 230;
	enemy1.size = 50;
	enemy1.oldrow = 5;
	enemy1.oldcol = 230;
	enemy1.rdel = 1;
	enemy1.cdel = 1;

	ENEMY enemy2;
	enemy2.row = 140;
	enemy2.col = 230;
	enemy2.size = 30;
	enemy2.oldrow = 140;
	enemy2.oldcol = 230;
	enemy2.rdel = 2;
	enemy2.cdel = 2;

	int bgcolor = LTGRAY;
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
	int score = 0;
	int scoreTimer = 0;
	char buffer[41];
	sprintf(buffer, "Score: %d", score);
	//char message[] = "Dear Mom, Send Money!";
	//char *mess = "Dear Mom, Send Money!";
	drawString(150, 5, buffer, YELLOW);

	// Fill screen with bgcolor using DBA
	REG_DMA3SAD = (u32)&bgcolor; // This is always an address!
	REG_DMA3DAD = (u32)videoBuffer; // This is always an address!
	REG_DMA3CNT = (240*160) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;

	drawString(150, 5, buffer, YELLOW);

	while(1)
	{
		
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			player.row = player.row - 2;
			if(player.row<=0)
			{
				player.row = 0;
			}
			scoreTimer++;
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			player.row = player.row + 2;
			if(player.row>=140)
			{
				player.row=140;
			}
			scoreTimer++;
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			player.col = player.col - 2;
			if(player.col<=0)
			{
				player.col=0;
			}
			scoreTimer++;
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			player.col = player.col + 2;
			if(player.col>=230)
			{
				player.col=230;
			}
			scoreTimer++;
		}
		drawRect(player.oldrow, player.oldcol, player.size, player.size, LTGRAY);
		drawRect(player.row, player.col, player.size, player.size, YELLOW);
		player.oldrow = player.row;
		player.oldcol = player.col;

		enemy1.row = enemy1.row + enemy1.rdel;
		enemy1.col = enemy1.col + enemy1.cdel;
		if(enemy1.row <= 0)
		{
			enemy1.row = 0;
			enemy1.rdel = -enemy1.rdel;
			scoreTimer++;
		}
		if(enemy1.row >= 140-enemy1.size)
		{
			enemy1.row = 140-enemy1.size;
			enemy1.rdel = -enemy1.rdel;
			scoreTimer++;
		}
		if(enemy1.col <= 0)
		{
			enemy1.col = 0;
			enemy1.cdel = -enemy1.cdel;
			scoreTimer++;
		}
		if(enemy1.col >= 230-enemy1.size)
		{
			enemy1.col = 230-enemy1.size;
			enemy1.cdel = -enemy1.cdel;
			scoreTimer++;
		}

		drawRect(enemy1.oldrow, enemy1.oldcol, enemy1.size, enemy1.size, LTGRAY);
		drawRect(enemy1.row, enemy1.col, enemy1.size, enemy1.size, RED);
		enemy1.oldrow = enemy1.row;
		enemy1.oldcol = enemy1.col;


		enemy2.row = enemy2.row + enemy2.rdel;
		enemy2.col = enemy2.col - enemy2.cdel;
		if(enemy2.row <= 0)
		{
			enemy2.row = 0;
			enemy2.rdel = -enemy2.rdel;
			scoreTimer++;
		}
		if(enemy2.row >= 140-enemy2.size)
		{
			enemy2.row = 140-enemy2.size;
			enemy2.rdel = -enemy2.rdel;
			scoreTimer++;
		}
		if(enemy2.col <= 0)
		{
			enemy2.col = 0;
			enemy2.cdel = -enemy2.cdel;
			scoreTimer++;
		}
		if(enemy2.col >= 230-enemy2.size)
		{
			enemy2.col = 230-enemy2.size;
			enemy2.cdel = -enemy2.cdel;
			scoreTimer++;
		}

		drawRect(enemy2.oldrow, enemy2.oldcol, enemy2.size, enemy2.size, LTGRAY);
		drawRect(enemy2.row, enemy2.col, enemy2.size, enemy2.size, BLUE);
		enemy2.oldrow = enemy2.row;
		enemy2.oldcol = enemy2.col;

		if (hit(player, enemy1) || hit(player, enemy2)) 
		{
			break;
		}

		drawRect(150, 5, 10, 70, LTGRAY);
		if (scoreTimer >= 50) {
			scoreTimer = 0;
			score++;
		}
		sprintf(buffer, "Score: %d", score);
		drawString(150, 5, buffer, YELLOW);

		waitForVblank();

		// if(KEY_DOWN_NOW(BUTTON_UP))
		// {
		// 	size = size + 1;
		// 	if(size>150)
		// 	{
		// 		size = 150;
		// 	}
		// }
		// if(KEY_DOWN_NOW(BUTTON_DOWN))
		// {
		// 	size = size - 1;
		// 	if(size<3)
		// 	{
		// 		size=3;
		// 	}
		// }
		// row = row + rdel;
		// col = col + cdel;
		// if(row < 0)
		// {
		// 	row = 0;
		// 	rdel = -rdel;
		// }
		// if(row > SCREENHEIGHT-size+1)
		// {
		// 	row = SCREENHEIGHT-size+1;
		// 	rdel = -rdel;
		// }
		// if(col < 0)
		// {
		// 	col = 0;
		// 	cdel = -cdel;
		// }
		// if(col > 239-size+1)
		// {
		// 	col = 239-size+1;
		// 	cdel = -cdel;
		// }
		// waitForVblank();
		// drawRect(150, 5, 10, 70, LTGRAY);
		// 		score++;
		// sprintf(buffer, "Score: %d", score);
		// drawString(150, 5, buffer, YELLOW);

		// drawRect(oldrow, oldcol, oldsize, oldsize, LTGRAY);
		// drawRect(row, col, size, size, YELLOW);
		// oldrow = row;
		// oldcol = col;
		// oldsize = size;
		
		
	}

}

int hit(PLAYER player, ENEMY enemy) 
{
	if (player.row >= enemy.row-player.size && player.row <= enemy.row+enemy.size && player.col >= enemy.col-player.size && player.col <= enemy.col+enemy.size)
	{
		//top edge
		return 1;
	}
	// if (player.row+player.size  enemy.row && player.row+player.size > enemy.row && player.col > enemy.col && player.col+player.size <= enemy.col)
	// {
	// 	return 1;
	// }
	// if ()
	return 0;
}

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r=0; r<height; r++)
	{
		REG_DMA3SAD = (u32)&color; // This is always an address!
		REG_DMA3DAD = (u32)&videoBuffer[OFFSET(row+r, col, 240)]; // This is always an address!
		//REG_DMA3DAD = (u32)(videoBuffer + OFFSET(row+r, col, 240) ); // This is always an address!
		REG_DMA3CNT = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
		/*for(int c=0; c<width; c++)
		{
			setPixel(row+r, col+c, color);
		}*/
	}
}


void delay(int n)
{
	volatile int x = 0;
	for(int i=0; i<n*5000; i++)
	{
		x = x + 1;
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void drawChar(int row, int col, char ch, unsigned short color)
{
	for(int r = 0; r< 8; r++)
	{
		for(int c=0; c< 6; c++)
		{
			if( fontdata_6x8[OFFSET(r, c, 6) + ch*48] == 1)
			{
				setPixel(r+row, c+col, color);
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