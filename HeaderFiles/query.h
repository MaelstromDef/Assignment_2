#pragma once

#include "utility.h"

enum query_type{
    NA = -1,
    max = 1,
    ratio = 2,
    find_occ = 3,
    range_occ = 4
};

query_type get_query(char[NUM_INPUTS][INPUT_LENGTH]);
void findMax(char[INPUT_LENGTH], int);
void findRatio(int, int);
void findOccupation();
void rangeOccupation();