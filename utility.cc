/*
 * utility.cc handles all the utility functions for the Assignment 2 CSE310 project
 */

#include "utility.h"

// Resets controller values to 0, allowing inputs[][] to be written to
void resetController(int* controller){
    for(int i = 0; i < 4; i++){
        controller[i] = 0;
    }
}