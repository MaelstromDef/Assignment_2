#ifndef QUERY_H
#define QUERY_H

#include "utility.h"

// Different types of queries that can be entered
enum query_type{
    NA = -1,        // NA is an undefined query_type. If get_query() returns NA, the query inputted was unrecognized.
    MAX = 1,
    RATIO = 2,
    FIND_OCC = 3,
    RANGE_OCC = 4
};

// Gets the query type entered into some 2d array of strings.
query_type get_query(char[NUM_INPUTS][INPUT_LENGTH]);

// The following 4 functions will perform the queries that can be entered into the program
void findMax(char workerType[INPUT_LENGTH], int numWorkers, int YYYY);
void findRatio(int, int);
void findOccupation();
void rangeOccupation();

#endif