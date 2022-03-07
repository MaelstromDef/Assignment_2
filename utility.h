#ifndef UTILITY_H
#define UTILITY_H

#include "defns.h"
#include <fstream>


#define NUM_INPUTS 4    // Max amount of inputs
#define INPUT_LENGTH 12    // Max length of inputs
#define SOC_FILE "Occupation-Dist-All-"   // File that contains SOC information
#define EARNINGS_FILE "Earnings-1960-2019.csv"    // File that contains yearly earnings information

enum worker_type{
    male = 1,
    female = 2,
    total = 3
};

enum SOC_detail{
    OCC = 1,
    CODE = 2,
    TOTAL = 3,
    FEMALE = 4
};

enum earnings_detail{
    year = 1,
    MT = 2,
    MWE = 3,
    ME = 4,
    MMOE = 5,
    FT = 6,
    FWE = 7,
    FE = 8
    // FMOE omitted due to lack of need
};

// resetController(int*) sets all values in an int[4] to 0.
void resetController(int* controller);

// intFromString(char[]) returns an int contained in a string.
// CAUTION: intFromString will keep parsing string "input" until '\0' is found, ignoring any non-digit text within it.
int intFromString(char* input);
// commaInt(int) prints out an int that is comma seperated (such as 1999 -> 1,999)
void commaInt(int toPrint);

// getSOC returns the address of an SOC array that was created using malloc.
SOC* getSOC(int YYYY);

#endif