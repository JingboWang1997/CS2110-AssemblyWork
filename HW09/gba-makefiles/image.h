/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=3 image end.jpg enemy1.jpg enemy2.jpg start.jpg food.png 
 * Time-stamp: Thursday 11/09/2017, 12:38:03
 * 
 * Image Information
 * -----------------
 * end.jpg 1280@720
 * enemy1.jpg 800@600
 * enemy2.jpg 800@600
 * start.jpg 1280@720
 * food.png 104@104
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

extern const unsigned short enemy1Image[1600];
#define ENEMY1_SIZE 3200
#define ENEMY1_LENGTH 1600
#define ENEMY1_WIDTH 40
#define ENEMY1_HEIGHT 40

extern const unsigned short enemy2Image[900];
#define ENEMY2_SIZE 1800
#define ENEMY2_LENGTH 900
#define ENEMY2_WIDTH 30
#define ENEMY2_HEIGHT 30

extern const unsigned short start[38400];
#define START_SIZE 76800
#define START_LENGTH 38400
#define START_WIDTH 240
#define START_HEIGHT 160

extern const unsigned short foodImage[25];
#define FOOD_SIZE 50
#define FOOD_LENGTH 25
#define FOOD_WIDTH 5
#define FOOD_HEIGHT 5

#endif

