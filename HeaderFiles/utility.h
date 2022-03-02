#pragma once

#include "defns.h"
#include <fstream>

#define NUM_INPUTS 4    // Max amount of inputs
#define INPUT_LENGTH 6    // Max length of inputs
#define SOC_FILE "./Occupation-Dist-All-YYYY.csv"

enum worker_type{
    male = 1,
    female = 2,
    total = 3
};

void resetController(int* controller);
int intFromString(char[INPUT_LENGTH]);
SOC** getSOC(SOC**, worker_type);