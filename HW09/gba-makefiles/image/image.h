/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=3 image end.jpg enemy1.jpg enemy2.jpg food.jpg player.png player2.jpg start.jpg 
 * Time-stamp: Friday 11/10/2017, 12:29:22
 * 
 * Image Information
 * -----------------
 * end.jpg 1280@720
 * enemy1.jpg 35@35
 * enemy2.jpg 25@25
 * food.jpg 15@16
 * player.png 25@26
 * player2.jpg 25@26
 * start.jpg 240@160
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef IMAGE_H
#define IMAGE_H

extern const unsigned short end[921600];
#define END_SIZE 1843200
#define END_LENGTH 921600
#define END_WIDTH 1280
#define END_HEIGHT 720

extern const unsigned short enemy1[1225];
#define ENEMY1_SIZE 2450
#define ENEMY1_LENGTH 1225
#define ENEMY1_WIDTH 35
#define ENEMY1_HEIGHT 35

extern const unsigned short enemy2[625];
#define ENEMY2_SIZE 1250
#define ENEMY2_LENGTH 625
#define ENEMY2_WIDTH 25
#define ENEMY2_HEIGHT 25

extern const unsigned short food[240];
#define FOOD_SIZE 480
#define FOOD_LENGTH 240
#define FOOD_WIDTH 15
#define FOOD_HEIGHT 16

extern const unsigned short player[650];
#define PLAYER_SIZE 1300
#define PLAYER_LENGTH 650
#define PLAYER_WIDTH 25
#define PLAYER_HEIGHT 26

extern const unsigned short player2[650];
#define PLAYER2_SIZE 1300
#define PLAYER2_LENGTH 650
#define PLAYER2_WIDTH 25
#define PLAYER2_HEIGHT 26

extern const unsigned short start[38400];
#define START_SIZE 76800
#define START_LENGTH 38400
#define START_WIDTH 240
#define START_HEIGHT 160

#endif

