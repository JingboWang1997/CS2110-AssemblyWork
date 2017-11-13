/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=3 image end.jpg enemy1.jpg enemy2.jpg food.jpg player.png player2.jpg start.jpg 
 * Time-stamp: Friday 11/10/2017, 14:26:42
 * 
 * Image Information
 * -----------------
 * end.jpg 240@160
 * enemy1.jpg 35@35
 * enemy2.jpg 25@25
 * food.jpg 15@15
 * player.png 25@25
 * player2.jpg 25@25
 * start.jpg 240@160
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef IMAGE_H
#define IMAGE_H

extern const unsigned short end[38400];
#define END_SIZE 76800
#define END_LENGTH 38400
#define END_WIDTH 240
#define END_HEIGHT 160

extern const unsigned short enemy1Image[1225];
#define ENEMY1_SIZE 2450
#define ENEMY1_LENGTH 1225
#define ENEMY1_WIDTH 35
#define ENEMY1_HEIGHT 35

extern const unsigned short enemy2Image[625];
#define ENEMY2_SIZE 1250
#define ENEMY2_LENGTH 625
#define ENEMY2_WIDTH 25
#define ENEMY2_HEIGHT 25

extern const unsigned short food[225];
#define FOOD_SIZE 450
#define FOOD_LENGTH 225
#define FOOD_WIDTH 15
#define FOOD_HEIGHT 15

extern const unsigned short playerImage[625];
#define PLAYER_SIZE 1250
#define PLAYER_LENGTH 625
#define PLAYER_WIDTH 25
#define PLAYER_HEIGHT 25

extern const unsigned short player2Image[625];
#define PLAYER2_SIZE 1250
#define PLAYER2_LENGTH 625
#define PLAYER2_WIDTH 25
#define PLAYER2_HEIGHT 25

extern const unsigned short start[38400];
#define START_SIZE 76800
#define START_LENGTH 38400
#define START_WIDTH 240
#define START_HEIGHT 160

extern const unsigned short bombImage[625];
#define BOMB_SIZE 1250
#define BOMB_LENGTH 625
#define BOMB_WIDTH 25
#define BOMB_HEIGHT 25

extern const unsigned short fireImage[625];
#define FIRE_SIZE 1250
#define FIRE_LENGTH 625
#define FIRE_WIDTH 25
#define FIRE_HEIGHT 25

#endif

