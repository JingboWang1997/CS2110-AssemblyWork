//fulltester.c
//Created by Cliff Panos

#include <stdio.h>
#include "diddyAnswer.h"
#include "diddy.h"
#include "balloonAnswer.h"
#include "balloon.h"
#include "smugcatAnswer.h"
#include "smugcat.h"
#include "smwabridgedAnswer.h"
#include "smwabridged.h"


int main()
{
    if (DIDDY_ANSWER_HEIGHT != DIDDY_HEIGHT) {
        printf("[DIDDY]: Found height of %d but expected height %d\n", DIDDY_HEIGHT, DIDDY_ANSWER_HEIGHT);
        return -1;
    }
    if (DIDDY_ANSWER_WIDTH != DIDDY_WIDTH) {
        printf("[DIDDY]: Found width of %d but expected width %d\n", DIDDY_WIDTH, DIDDY_ANSWER_WIDTH);
        return -1;
    }

    //At this point, it is mostly safe to go through both arrays and compare
    unsigned int diddyLength = sizeof(diddy_answer_data) / sizeof(diddy_answer_data[0]);
    unsigned int multipliedSize = DIDDY_WIDTH * DIDDY_HEIGHT;
    if (multipliedSize != diddyLength)
    {
        printf("[DIDDY]: Error with format of nex numbers inputted into the array\n");
        return -1;
    }


    printf("\n[DIDDY ARRAY TEST] Size of array to check: %d\n", diddyLength);
    int diddySuccess = 1;
    for (unsigned int i = 0; i < diddyLength; i++)
    {
        //Uncomment this to print the contents of the array
        //printf("0x%04x \n", diddy_data[i]);
        if (diddy_answer_data[i] - diddy_data[i] != 0) {
            printf("[DIDDY ARRAY TEST] Failure: The arrays differed at element %d; expected 0x%04x but was 0x%04x\n", i, diddy_answer_data[i], diddy_data[i]);
            diddySuccess = 0;
            break;
        }
    }

    if (diddySuccess) printf("[DIDDY ARRAY TEST] Success! The arrays are equal :D\n");




    unsigned int balloonLength = sizeof(balloon_answer_data) / sizeof(balloon_answer_data[0]);

    printf("\n[BALLOON ARRAY TEST] Size of array to check: %d\n", balloonLength);
    int balloonSuccess = 1;
    for (unsigned int i = 0; i < balloonLength; i++)
    {
        if (balloon_answer_data[i] - balloon_data[i] != 0) {
            printf("[BALLOON ARRAY TEST] Failure: The arrays differed at element %d; expected 0x%04x but was 0x%04x\n", i, balloon_answer_data[i], balloon_data[i]);
            balloonSuccess = 0;
            break;
        }
    }

    if (balloonSuccess) printf("[BALLOON ARRAY TEST] Success! The arrays are equal :D\n");




    unsigned int smugcatLength = sizeof(smugcat_answer_data) / sizeof(smugcat_answer_data[0]);

    printf("\n[SMUGCAT ARRAY TEST] Size of array to check: %d\n", smugcatLength);
    int smugcatSuccess = 1;
    for (unsigned int i = 0; i < smugcatLength; i++)
    {
        if (smugcat_answer_data[i] - smugcat_data[i] != 0) {
            printf("[SMUGCAT ARRAY TEST] Failure: The arrays differed at element %d; expected 0x%04x but was 0x%04x\n", i, smugcat_answer_data[i], smugcat_data[i]);
            smugcatSuccess = 0;
            break;
        }
    }

    //At this point, the check is complete! Success!
    if (smugcatSuccess) printf("[SMUGCAT ARRAY TEST] Success! The arrays are equal :D\n");




    unsigned int smwabridgedLength = sizeof(smwabridged_answer_data) / sizeof(smwabridged_answer_data[0]);

    printf("\n[SMWABRIDGED ARRAY TEST] Size of array to check: %d\n", smwabridgedLength);
    int smwabridgedSuccess = 1;
    for (unsigned int i = 0; i < smwabridgedLength; i++)
    {
        if (smwabridged_answer_data[i] - smwabridged_data[i] != 0) {
            printf("[SMWABRIDGED ARRAY TEST] Failure: The arrays differed at element %d; expected 0x%04x but was 0x%04x\n", i, smwabridged_answer_data[i], smwabridged_data[i]);
            smwabridgedSuccess = 0;
            break;
        }
    }

    //At this point, the check is complete! Success!
    if (smwabridgedSuccess) printf("[SMWABRIDGED ARRAY TEST] Success! The arrays are equal :D\n");

    int totalSuccesses = diddySuccess + balloonSuccess + smugcatSuccess + smwabridgedSuccess;
    //printf("Total: %d\n", totalSuccesses);

    return totalSuccesses;
}
