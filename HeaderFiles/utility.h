#ifndef UTILITY_H
#define UTILITY_H

#include "defns.h"
#include <fstream>


#define NUM_INPUTS 4    // Max amount of inputs
#define INPUT_LENGTH 12    // Max length of inputs
#define SOC_FILE "./Occupation-Dist-All-YYYY.csv"   // File that contains SOC information

enum worker_type{
    male = 1,
    female = 2,
    total = 3
};

// resetController(int*) sets all values in an int[4] to 0.
void resetController(int* controller);
// intFromString(char[]) returns an int contained in a string
int intFromString(char[INPUT_LENGTH]);
// getSOC returns the address of an SOC array that was created using malloc.
SOC* getSOC();

#endif