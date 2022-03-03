//
// Created by cse310 on 2/27/22.
//

#ifndef HEAP_H
#define HEAP_H

#include "defns.h"

// Basic function of "heap.cc". Since "heap.cc" has no basic purpose outside it's other functions, heap() returns 0.
int heap();

// Heap functions of "heap.cc"
int MAX_HEAPIFY(SOC*, int, int);
int DELETE_MAX(SOC*, int);
int BUILD_MAX_HEAP(SOC*, int);

#endif