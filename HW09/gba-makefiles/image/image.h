/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=3 image end.jpg enemy1.jpg enemy2.jpg start.jpg food.png 
 * Time-stamp: Friday 11/10/2017, 00:15:35
 * 
 * Image Information
 * -----------------
 * end.jpg 1280@720
 * enemy1.jpg 40@40
 * enemy2.jpg 30@30
 * start.jpg 240@160
 * food.png 5@5
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

extern const unsigned short enemy1[1600];
#define ENEMY1_SIZE 3200
#define ENEMY1_LENGTH 1600
#define ENEMY1_WIDTH 40
#define ENEMY1_HEIGHT 40

extern const unsigned short enemy2[900];
#define ENEMY2_SIZE 1800
#define ENEMY2_LENGTH 900
#define ENEMY2_WIDTH 30
#define ENEMY2_HEIGHT 30

extern const unsigned short start[38400];
#define START_SIZE 76800
#define START_LENGTH 38400
#define START_WIDTH 240
#define START_HEIGHT 160

extern const unsigned short food[25];
#define FOOD_SIZE 50
#define FOOD_LENGTH 25
#define FOOD_WIDTH 5
#define FOOD_HEIGHT 5

#endif

