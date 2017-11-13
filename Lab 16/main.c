#include "myLib.h"
#include "my_images.h"

int main() {

    // You should not need to edit any of this code.
    // If you want to test with other images comment this out
    // and replace it with your own tests.
    REG_DISPCNT = MODE_3 | BG2_ENABLE;
    
    drawImage(0, 0, Q1_WIDTH, Q1_HEIGHT, q1);
    drawImageFlippedLR(0, 120, Q2_WIDTH, Q2_HEIGHT, q2);
    drawImageFlippedUD(80, 0, Q3_WIDTH, Q3_HEIGHT, q3);
    drawImage(80, 120, Q4_WIDTH, Q4_HEIGHT, q4);

    drawRedRectangle(5, 5, 20, 20);
    drawRedRectangle(135, 5, 20, 20);
    drawRedRectangle(5, 215, 20, 20);
    drawRedRectangle(135, 215, 20, 20);

    while(1);
}