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
				drawString(150, 5, "Press A to START", WHITE);
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
				player.size = 25;
				player.oldrow = 5;
				player.oldcol = 5;
				player.rdel = 2;
				player.cdel = 2;
				player.flag = 1;
				player.image = playerImage;

				OBJECT enemy1;
				enemy1.row = 0;
				enemy1.col = 205;
				enemy1.size = 35;
				enemy1.oldrow = 0;
				enemy1.oldcol = 205;
				enemy1.rdel = 1;
				enemy1.cdel = 1;
				enemy1.flag = 1;
				enemy1.image = enemy1Image;

				OBJECT enemy2;
				enemy2.row = 115;
				enemy2.col = 215;
				enemy2.size = 25;
				enemy2.oldrow = 115;
				enemy2.oldcol = 215;
				enemy2.rdel = 2;
				enemy2.cdel = 2;
				enemy2.flag = 1;
				enemy2.image = enemy2Image;

				OBJECT speed;
				speed.row = 50;
				speed.col = 50;
				speed.size = 15;
				speed.oldrow = 50;
				speed.oldcol = 50;
				speed.rdel = -1;
				speed.cdel = -1;
				speed.flag = 1;
				speed.image = food;

				break;
			case GAME:
				//operations
				if(KEY_DOWN_NOW(BUTTON_UP))
				{
					if (player.rdel > 0) 
					{
						player.rdel = -player.rdel;
					}
					player.row = player.row + player.rdel;
					if(player.row <= 0)
					{
						player.row = 0;
					}
					else
					{
						scoreTimer++;
					}
				}
				if(KEY_DOWN_NOW(BUTTON_DOWN))
				{
					if (player.rdel < 0) 
					{
						player.rdel = -player.rdel;
					}
					player.row = player.row + player.rdel;
					if(player.row >= 140 - player.size)
					{
						player.row = 140 - player.size;
					}
					else
					{
						scoreTimer++;
					}
				}
				if(KEY_DOWN_NOW(BUTTON_LEFT))
				{
					if (player.cdel > 0) 
					{
						player.cdel = -player.cdel;
					}
					player.col = player.col + player.cdel;
					if(player.col <= 0)
					{
						player.col = 0;
					}
					else
					{
						scoreTimer++;
					}
				}
				if(KEY_DOWN_NOW(BUTTON_RIGHT))
				{
					if (player.cdel < 0) 
					{
						player.cdel = -player.cdel;
					}
					player.col = player.col + player.cdel;
					if(player.col >= 240 - player.size)
					{
						player.col = 240 - player.size;
					}
					else
					{
						scoreTimer++;
					}
				}
				//erase the old one
				drawRect(player.oldrow, player.oldcol, player.size, player.size, bgcolor);
				//direction of movement change image
				if (player.cdel > 0)
				{
					drawImageRL(player.row, player.col, player.size, player.size, player.image);
				}
				else
				{
					drawImage(player.row, player.col, player.size, player.size, player.image);
				}
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
				drawImage(enemy1.row, enemy1.col, enemy1.size, enemy1.size, enemy1.image);
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
				drawImage(enemy2.row, enemy2.col, enemy2.size, enemy2.size, enemy2.image);
				//drawRect(enemy2.row, enemy2.col, enemy2.size, enemy2.size, RED);
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
					drawImage(speed.row, speed.col, speed.size, speed.size, speed.image);
					speed.oldrow = speed.row;
					speed.oldcol = speed.col;

					if (collide(player, speed))
					{
						if (player.rdel > 0) 
						{
							player.rdel++;
						}
						else
						{
							player.rdel--;
						}
						if (player.cdel > 0) 
						{
							player.cdel++;
						}
						else
						{
							player.cdel--;
						}
						speed.flag = 0;
						foodTimer = 0;
						player.image = player2Image;
						drawRect(speed.row, speed.col, speed.size, speed.size, bgcolor);
					}
				}
				else
				{
					drawRect(150, 165, 10, 70, bgcolor);
					sprintf(buffer, "Speed Timer: %d", 5-foodTimer);
					drawString(150, 145, buffer, BLUE);
					if (foodTimer > 5)
					{
						drawRect(150, 145, 10, 90, bgcolor);
						player.image = playerImage;
						speed.flag = 1;
						if (player.rdel > 0) 
						{
							player.rdel--;
						}
						else
						{
							player.rdel++;
						}
						if (player.cdel > 0) 
						{
							player.cdel--;
						}
						else
						{
							player.cdel++;
						}
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
						foodTimer++;
						
					}
				}

				//key release listener
				if (!KEY_DOWN_NOW(BUTTON_A)) 
				{
					released = 1;
				}

				//key interuption listener
				if (KEY_DOWN_NOW(BUTTON_SELECT))
				{
					state = START;
				}
				break;
			case END:
				//end screen
		        drawImage(0, 0, END_WIDTH, END_HEIGHT, end);
				sprintf(buffer, "Your score is: %d", score);
				drawString(100, 70, buffer, YELLOW);
				drawString(150, 10, "Press A or SELETE to EXIT", WHITE);
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
				if (KEY_DOWN_NOW(BUTTON_SELECT))
				{
					state = START;
				}
				break;
		}
	waitForVblank();
	}
}