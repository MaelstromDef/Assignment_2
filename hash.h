//
// Created by cse310 on 3/25/22.
//

#ifndef ASSIGNMENT_2_HASH_H
#define ASSIGNMENT_2_HASH_H

#define m 1523  // Size of the hash table

#include "defns.h"

// Returns the index in a hash table of a certain soc code
int h(int k);

// Creates a hash entry given some bst node
void createHashEntry(bst* node);

#endif //ASSIGNMENT_2_HASH_H
