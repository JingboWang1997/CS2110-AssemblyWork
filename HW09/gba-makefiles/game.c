#include <stdio.h>
#include "myLib.h"
#include "text.h"
#include "image.h"

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	enum GBAState state = START;
	int released = 0;
	u16 bgcolor = WHITE;
	int score = 0;
	int scoreTimer = 0;
	int foodTimer = 0;
	char buffer[41];

	while(1)
	{
		switch(state) 
		{
			case START:
				//start screen
		        drawImage(0, 0, START_WIDTH, START_HEIGHT, start);
				drawString(140, 5, "Press Z to START", BLUE);
				state = START_NODRAW;
				break;
			case START_NODRAW:
				//no draw state to maintain start screen
				state = START_NODRAW;
				if (!KEY_DOWN_NOW(BUTTON_A)) 
				{
					released = 1;
				}
				if (KEY_DOWN_NOW(BUTTON_A) && released) 
				{
					state = GAME_SETUP;
					released = 0;
				}
				break;
			case GAME_SETUP:
				//initialize the game screen and objects
		        drawRect(0, 0, 160, 240, bgcolor);

				state = GAME;
				score = 0;
				scoreTimer = 0;
				foodTimer = 0;

				OBJECT player;
				player.row = 5;
				player.col = 5;
				player.size = 10;
				player.oldrow = 5;
				player.oldcol = 5;
				player.rdel = 2;
				player.cdel = 2;
				player.flag = 1;

				OBJECT enemy1;
				enemy1.row = 5;
				enemy1.col = 230;
				enemy1.size = 40;
				enemy1.oldrow = 5;
				enemy1.oldcol = 230;
				enemy1.rdel = 1;
				enemy1.cdel = 1;
				enemy1.flag = 1;

				OBJECT enemy2;
				enemy2.row = 140;
				enemy2.col = 230;
				enemy2.size = 30;
				enemy2.oldrow = 140;
				enemy2.oldcol = 230;
				enemy2.rdel = 2;
				enemy2.cdel = 2;
				enemy2.flag = 1;

				OBJECT speed;
				speed.row = 50;
				speed.col = 50;
				speed.size = 5;
				speed.oldrow = 50;
				speed.oldcol = 50;
				speed.rdel = -1;
				speed.cdel = -1;
				speed.flag = 1;

				break;
			case GAME:
				//operations
				if(KEY_DOWN_NOW(BUTTON_UP))
				{
					player.row = player.row - player.rdel;
					if(player.row <= 0)
					{
						player.row = 0;
					}
					scoreTimer++;
				}
				if(KEY_DOWN_NOW(BUTTON_DOWN))
				{
					player.row = player.row + player.rdel;
					if(player.row >= 140 - player.size)
					{
						player.row = 140 - player.size;
					}
					scoreTimer++;
				}
				if(KEY_DOWN_NOW(BUTTON_LEFT))
				{
					player.col = player.col - player.cdel;
					if(player.col <= 0)
					{
						player.col = 0;
					}
					scoreTimer++;
				}
				if(KEY_DOWN_NOW(BUTTON_RIGHT))
				{
					player.col = player.col + player.cdel;
					if(player.col >= 240 - player.size)
					{
						player.col = 240 - player.size;
					}
					scoreTimer++;
				}
				//erase the old one
				drawRect(player.oldrow, player.oldcol, player.size, player.size, bgcolor);
				//track if the player in high-speed mode or normal mode
				if (speed.flag) 
				{
					drawRect(player.row, player.col, player.size, player.size, DKGRAY);
				}
				else
				{
					drawRect(player.row, player.col, player.size, player.size, BLUE);
				}
				//update player location
				player.oldrow = player.row;
				player.oldcol = player.col;

				//enemy1 movement
				enemy1.row = enemy1.row + enemy1.rdel;
				enemy1.col = enemy1.col + enemy1.cdel;
				if(enemy1.row <= 0)
				{
					enemy1.row = 0;
					enemy1.rdel = -enemy1.rdel;
				}
				if(enemy1.row >= 140-enemy1.size)
				{
					enemy1.row = 140-enemy1.size;
					enemy1.rdel = -enemy1.rdel;
				}
				if(enemy1.col <= 0)
				{
					enemy1.col = 0;
					enemy1.cdel = -enemy1.cdel;
				}
				if(enemy1.col >= 240-enemy1.size)
				{
					enemy1.col = 240-enemy1.size;
					enemy1.cdel = -enemy1.cdel;
				}
				drawRect(enemy1.oldrow, enemy1.oldcol, enemy1.size, enemy1.size, bgcolor);
				drawImage(enemy1.row, enemy1.col, ENEMY1_WIDTH, ENEMY1_HEIGHT, enemy1Image);
				enemy1.oldrow = enemy1.row;
				enemy1.oldcol = enemy1.col;

				//enemy2 movement
				enemy2.row = enemy2.row + enemy2.rdel;
				enemy2.col = enemy2.col - enemy2.cdel;
				if(enemy2.row <= 0)
				{
					enemy2.row = 0;
					enemy2.rdel = -enemy2.rdel;
				}
				if(enemy2.row >= 140-enemy2.size)
				{
					enemy2.row = 140-enemy2.size;
					enemy2.rdel = -enemy2.rdel;
				}
				if(enemy2.col <= 0)
				{
					enemy2.col = 0;
					enemy2.cdel = -enemy2.cdel;
				}
				if(enemy2.col >= 240-enemy2.size)
				{
					enemy2.col = 240-enemy2.size;
					enemy2.cdel = -enemy2.cdel;
				}
				drawRect(enemy2.oldrow, enemy2.oldcol, enemy2.size, enemy2.size, bgcolor);
				drawImage(enemy2.row, enemy2.col, ENEMY2_WIDTH, ENEMY2_HEIGHT, enemy2Image);
				enemy2.oldrow = enemy2.row;
				enemy2.oldcol = enemy2.col;

				//speed potion movement
				if (speed.flag) 
				{
					speed.row = speed.row + speed.rdel;
					speed.col = speed.col - speed.cdel;
					if(speed.row <= 0)
					{
						speed.row = 0;
						speed.rdel = -speed.rdel;
					}
					if(speed.row >= 140-speed.size)
					{
						speed.row = 140-speed.size;
						speed.rdel = -speed.rdel;
					}
					if(speed.col <= 0)
					{
						speed.col = 0;
						speed.cdel = -speed.cdel;
					}
					if(speed.col >= 240-speed.size)
					{
						speed.col = 240-speed.size;
						speed.cdel = -speed.cdel;
					}
					drawRect(speed.oldrow, speed.oldcol, speed.size, speed.size, bgcolor);
					drawImage(speed.row, speed.col, FOOD_WIDTH, FOOD_HEIGHT, food);
					speed.oldrow = speed.row;
					speed.oldcol = speed.col;

					if (collide(player, speed))
					{
						player.rdel++;
						player.cdel++;

						speed.flag = 0;
						drawRect(speed.row, speed.col, speed.size, speed.size, bgcolor);
					}
				}

				//collision listener
				if (collide(player, enemy1) || collide(player, enemy2)) 
				{
					state = END;
				}

				//score update
				drawRect(140, 0, 1, 240, RED);
				drawRect(150, 5, 10, 70, bgcolor);
				sprintf(buffer, "Score: %d", score);
				drawString(150, 5, buffer, RED);

				//speed-mode timer
				if (scoreTimer >= 80) //for each 80 pixels it moved
				{
					scoreTimer = 0;
					score++;
					if (!speed.flag)
					{
						drawRect(150, 140, 10, 70, bgcolor);
						sprintf(buffer, "Speed Timer: %d", 11-foodTimer-1);
						drawString(150, 120, buffer, BLUE);
						foodTimer++;
						if (foodTimer >= 11)
						{
							drawRect(150, 120, 10, 100, bgcolor);
							foodTimer = 0;
							speed.flag = 1;
							player.rdel--;
							player.cdel--;
						}
					}
				}

				//key release listener
				if (!KEY_DOWN_NOW(BUTTON_A)) 
				{
					released = 1;
				}

				//key interuption listener
				if (KEY_DOWN_NOW(BUTTON_A) && released) 
				{
					state = START;
					released = 0;
				}
				waitForVblank();
				break;
			case END:
				//end screen
		        drawImage(0, 0, END_WIDTH, END_HEIGHT, end);
				sprintf(buffer, "Your score is: %d", score);
				drawString(100, 70, buffer, YELLOW);
				drawString(10, 10, "Press Z to EXIT", BLUE);
				state = END_NODRAW;

			case END_NODRAW:
				//maintain end screen
				state = END_NODRAW;
				if (!KEY_DOWN_NOW(BUTTON_A)) 
				{
					released = 1;
				}
				if (KEY_DOWN_NOW(BUTTON_A) && released) 
				{
					state = START;
					released = 0;
				}
				break;
		}
	}
}