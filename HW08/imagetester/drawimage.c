// Put any additional header includes here

#include "smwabridged.h"

void drawImage(int width, int height, const unsigned short *image_data);
void draw_an_image() {

    // Make a call to draw the image here
    drawImage(SMWABRIDGED_WIDTH, SMWABRIDGED_HEIGHT, smwabridged_data);
    //drawImage(BALLOON_WIDTH, BALLOON_HEIGHT, balloon_data);

}

