#include <stdio.h>
#include "myLib.h"
#include "text.h"
#include "image.h"

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	enum GBAState state = START;
	int releasedA = 0;
	int releasedB = 0;
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
		        drawString(140, 5, "Press A to Dodge Mode", WHITE);
				drawString(150, 5, "Press B to Bomb Mode", WHITE);
				state = START_NODRAW;
				break;
			case START_NODRAW:
				//no draw state to maintain start screen
				state = START_NODRAW;
				if (!KEY_DOWN_NOW(BUTTON_A)) 
				{
					releasedA = 1;
				}
				if (KEY_DOWN_NOW(BUTTON_A) && releasedA) 
				{
					state = GAME1_SETUP;
					releasedA = 0;
				}
				if (!KEY_DOWN_NOW(BUTTON_B)) 
				{
					releasedB = 1;
				}
				if (KEY_DOWN_NOW(BUTTON_B) && releasedB) 
				{
					state = GAME2_SETUP;
					releasedB = 0;
				}
				break;
			case GAME1_SETUP:
				//initialize the game screen and objects
		        drawRect(0, 0, 160, 240, bgcolor);

				state = GAME1;
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
			case GAME1:
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

				//key interuption listener
				if (KEY_DOWN_NOW(BUTTON_SELECT))
				{
					state = START;
				}
				break;
			case GAME2_SETUP:
				//initialize the game screen and objects
			 	drawRect(0, 0, 160, 240, BLACK);
		        drawRect(0, 25, 160, 200, bgcolor);

				state = GAME2;

				int timer = 0;

				OBJECT player2;
				player2.row = 0;
				player2.col = 25;
				player2.size = 25;
				player2.oldrow = 0;
				player2.oldcol = 25;
				player2.rdel = 3;
				player2.cdel = 3;
				player2.flag = 1;
				player2.image = player2Image;

				OBJECT enemy1_1;
				enemy1_1.row = 0;
				enemy1_1.col = 190;
				enemy1_1.size = 35;
				enemy1_1.oldrow = 0;
				enemy1_1.oldcol = 190;
				enemy1_1.rdel = 1;
				enemy1_1.cdel = 1;
				enemy1_1.flag = 1;
				enemy1_1.image = enemy1Image;

				OBJECT enemy2_2;
				enemy2_2.row = 135;
				enemy2_2.col = 200;
				enemy2_2.size = 25;
				enemy2_2.oldrow = 135;
				enemy2_2.oldcol = 200;
				enemy2_2.rdel = 2;
				enemy2_2.cdel = 2;
				enemy2_2.flag = 1;
				enemy2_2.image = enemy2Image;

				OBJECT bomb;
				bomb.row = 0;
				bomb.col = 0;
				bomb.size = 25;
				bomb.oldrow = 0;
				bomb.oldcol = 0;
				bomb.rdel = 0;
				bomb.cdel = 0;
				bomb.flag = 0;
				bomb.image = bombImage;

				OBJECT fire1;
				fire1.row = 0;
				fire1.col = 0;
				fire1.size = 25;
				fire1.oldrow = 0;
				fire1.oldcol = 0;
				fire1.rdel = 0;
				fire1.cdel = 0;
				fire1.flag = 0;
				fire1.image = fireImage;

				OBJECT fire2;
				fire2.row = 0;
				fire2.col = 0;
				fire2.size = 25;
				fire2.oldrow = 0;
				fire2.oldcol = 0;
				fire2.rdel = 0;
				fire2.cdel = 0;
				fire2.flag = 0;
				fire2.image = fireImage;

				OBJECT fire3;
				fire3.row = 0;
				fire3.col = 0;
				fire3.size = 25;
				fire3.oldrow = 0;
				fire3.oldcol = 0;
				fire3.rdel = 0;
				fire3.cdel = 0;
				fire3.flag = 0;
				fire3.image = fireImage;

				OBJECT fire4;
				fire4.row = 0;
				fire4.col = 0;
				fire4.size = 25;
				fire4.oldrow = 0;
				fire4.oldcol = 0;
				fire4.rdel = 0;
				fire4.cdel = 0;
				fire4.flag = 0;
				fire4.image = fireImage;

				break;
			case GAME2:

				if (!enemy1_1.flag && !enemy2_2.flag)
				{
					state = SUCCESS2;
				}

				//operations
				if(KEY_DOWN_NOW(BUTTON_UP))
				{
					if (player2.rdel > 0) 
					{
						player2.rdel = -player2.rdel;
					}
					player2.row = player2.row + player2.rdel;
					if(player2.row <= 0)
					{
						player2.row = 0;
					}
				}
				if(KEY_DOWN_NOW(BUTTON_DOWN))
				{
					if (player2.rdel < 0) 
					{
						player2.rdel = -player2.rdel;
					}
					player2.row = player2.row + player2.rdel;
					if(player2.row >= 160 - player2.size)
					{
						player2.row = 160 - player2.size;
					}
				}
				if(KEY_DOWN_NOW(BUTTON_LEFT))
				{
					if (player2.cdel > 0) 
					{
						player2.cdel = -player2.cdel;
					}
					player2.col = player2.col + player2.cdel;
					if(player2.col <= 25)
					{
						player2.col = 25;
					}
				}
				if(KEY_DOWN_NOW(BUTTON_RIGHT))
				{
					if (player2.cdel < 0) 
					{
						player2.cdel = -player2.cdel;
					}
					player2.col = player2.col + player2.cdel;
					if(player2.col >= 225 - player2.size)
					{
						player2.col = 225 - player2.size;
					}
				}
				//erase the old one
				drawRect(player2.oldrow, player2.oldcol, player2.size, player2.size, bgcolor);
				//direction of movement change image
				if (player2.cdel > 0)
				{
					drawImageRL(player2.row, player2.col, player2.size, player2.size, player2.image);
				}
				else
				{
					drawImage(player2.row, player2.col, player2.size, player2.size, player2.image);
				}
				player2.oldrow = player2.row;
				player2.oldcol = player2.col;

				//enemy1 movement
				if (enemy1_1.flag)
				{
					enemy1_1.row = enemy1_1.row + enemy1_1.rdel;
					enemy1_1.col = enemy1_1.col + enemy1_1.cdel;
					if(enemy1_1.row <= 0)
					{
						enemy1_1.row = 0;
						enemy1_1.rdel = -enemy1_1.rdel;
					}
					if(enemy1_1.row >= 160-enemy1_1.size)
					{
						enemy1_1.row = 160-enemy1_1.size;
						enemy1_1.rdel = -enemy1_1.rdel;
					}
					if(enemy1_1.col <= 25)
					{
						enemy1_1.col = 25;
						enemy1_1.cdel = -enemy1_1.cdel;
					}
					if(enemy1_1.col >= 225-enemy1_1.size)
					{
						enemy1_1.col = 225-enemy1_1.size;
						enemy1_1.cdel = -enemy1_1.cdel;
					}
					drawRect(enemy1_1.oldrow, enemy1_1.oldcol, enemy1_1.size, enemy1_1.size, bgcolor);
					drawImage(enemy1_1.row, enemy1_1.col, enemy1_1.size, enemy1_1.size, enemy1_1.image);
					enemy1_1.oldrow = enemy1_1.row;
					enemy1_1.oldcol = enemy1_1.col;
				}
				

				//enemy2 movement
				if (enemy2_2.flag)
				{
					enemy2_2.row = enemy2_2.row - enemy2_2.rdel;
					enemy2_2.col = enemy2_2.col - enemy2_2.cdel;
					if(enemy2_2.row <= 0)
					{
						enemy2_2.row = 0;
						enemy2_2.rdel = -enemy2_2.rdel;
					}
					if(enemy2_2.row >= 160-enemy2_2.size)
					{
						enemy2_2.row = 160-enemy2_2.size;
						enemy2_2.rdel = -enemy2_2.rdel;
					}
					if(enemy2_2.col <= 25)
					{
						enemy2_2.col = 25;
						enemy2_2.cdel = -enemy2_2.cdel;
					}
					if(enemy2_2.col >= 225-enemy2_2.size)
					{
						enemy2_2.col = 225-enemy2_2.size;
						enemy2_2.cdel = -enemy2_2.cdel;
					}
					drawRect(enemy2_2.oldrow, enemy2_2.oldcol, enemy2_2.size, enemy2_2.size, bgcolor);
					drawImage(enemy2_2.row, enemy2_2.col, enemy2_2.size, enemy2_2.size, enemy2_2.image);
					enemy2_2.oldrow = enemy2_2.row;
					enemy2_2.oldcol = enemy2_2.col;
				}

				if ((collide(player2, fire1) || collide(player2, fire2) || collide(player2, fire3) || collide(player2, fire4) || collide(player2, bomb)) && fire1.flag)
				{
					state = END2;
				}

				if ((collide(enemy1_1, fire1) || collide(enemy1_1, fire2) || collide(enemy1_1, fire3) || collide(enemy1_1, fire4) || collide(enemy1_1, bomb)) && fire1.flag)
				{
					enemy1_1.flag = 0;
					drawRect(enemy1_1.oldrow, enemy1_1.oldcol, enemy1_1.size, enemy1_1.size, bgcolor);
				}

				if ((collide(enemy2_2, fire1) || collide(enemy2_2, fire2) || collide(enemy2_2, fire3) || collide(enemy2_2, fire4) || collide(enemy2_2, bomb)) && fire1.flag)
				{
					enemy2_2.flag = 0;
					drawRect(enemy2_2.oldrow, enemy2_2.oldcol, enemy2_2.size, enemy2_2.size, bgcolor);
				}


				if (bomb.flag)
				{
					drawImage(bomb.row, bomb.col, bomb.size, bomb.size, bomb.image);
					timer++;
				}

				if (fire1.flag)
				{
					drawImage(fire1.row, fire1.col, fire1.size, fire1.size, fire1.image);
					drawImage(fire2.row, fire2.col, fire2.size, fire2.size, fire2.image);
					if (fire2.col < 25)
					{
						drawRect(fire2.row, fire2.col, fire1.size, 25-fire2.col, BLACK);
					}
					drawImage(fire3.row, fire3.col, fire3.size, fire3.size, fire3.image);
					drawImage(fire4.row, fire4.col, fire4.size, fire4.size, fire4.image);
					if (fire4.col+fire4.size > 225)
					{
						drawRect(fire4.row, 225, fire4.size, fire4.col+fire4.size-225, BLACK);
					}

				}

				if (timer >= 100)
				{
					//put fire next to bomb
					fire1.row = bomb.row-fire1.size;
					fire1.col = bomb.col;
					fire1.flag = 1;

					fire2.row = bomb.row;
					fire2.col = bomb.col-fire2.size;
					fire2.flag = 1;

					fire3.row = bomb.row+fire3.size;
					fire3.col = bomb.col;
					fire3.flag = 1;

					fire4.row = bomb.row;
					fire4.col = bomb.col+fire4.size;
					fire4.flag = 1;

				}

				if (timer >= 120)
				{
					timer = 0;
					bomb.flag = 0;
					fire1.flag = 0;
					fire2.flag = 0;
					fire3.flag = 0;
					fire4.flag = 0;

					drawRect(bomb.row, bomb.col, bomb.size, bomb.size, bgcolor);
					drawRect(fire1.row, fire1.col, fire1.size, fire1.size, bgcolor);
					drawRect(fire2.row, fire2.col, fire2.size, fire2.size, bgcolor);
					if (fire2.col < 25)
					{
						drawRect(fire2.row, fire2.col, fire1.size, 25-fire2.col, BLACK);
					}
					drawRect(fire3.row, fire3.col, fire3.size, fire3.size, bgcolor);
					drawRect(fire4.row, fire4.col, fire4.size, fire4.size, bgcolor);
					if (fire4.col+fire4.size > 225)
					{
						drawRect(fire4.row, 225, fire4.size, fire4.col+fire4.size-225, BLACK);
					}

				}

				if (KEY_DOWN_NOW(BUTTON_A))
				{
					if (!bomb.flag && player2.row >= 0 && player2.row <= 160 && player2.col - 10 >= 0 && player2.row + 15 <= 240)
					{
						bomb.row = player2.row;
						bomb.col = player2.col;
						bomb.flag = 1;
					}
				}

				//collision listener
				if ((collide(player2, enemy1_1) && enemy1_1.flag) || (collide(player2, enemy2_2) && enemy2_2.flag)) 
				{
					state = END2;
				}

				//key release listener
				if (!KEY_DOWN_NOW(BUTTON_B)) 
				{
					releasedB = 1;
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
				drawString(150, 10, "Press SELETE to EXIT", WHITE);
				state = END_NODRAW;
				break;
			case END2:
				//end screen
		        drawImage(0, 0, END_WIDTH, END_HEIGHT, end);
				drawString(100, 95, "YOU LOST!", YELLOW);
				drawString(150, 10, "Press SELETE to EXIT", WHITE);
				state = END_NODRAW;
				break;
			case SUCCESS2:
				//end screen
		        drawImage(0, 0, END_WIDTH, END_HEIGHT, end);
				drawString(100, 70, "YOU WIN!", YELLOW);
				drawImage(90, 130, 25, 25, player2Image);
				drawString(150, 10, "Press SELETE to EXIT", WHITE);
				state = END_NODRAW;
				break;
			case END_NODRAW:
				//maintain end screen
				state = END_NODRAW;
				if (KEY_DOWN_NOW(BUTTON_SELECT))
				{
					state = START;
				}
				break;
		}
	waitForVblank();
	}
}