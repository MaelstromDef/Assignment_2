/*
 * heap.cc handles all heap functions for the Assignment 2 CSE310 project
 */

#include "../HeaderFiles/heap.h"
#include <iostream>

int heap(){
    return 0;
}

// Maintains Max Heap structure of an array
/*
 * Takes 3 inputs: socArray, i, and size.
 * socArray is a pointer to a SOC array.
 * i is the index of the heap element to be MAX_HEAPIFY'd (+ 1 for ease of use).
 * size is the total size of the socArray
 */
int MAX_HEAPIFY(SOC* socArray, int i, int size){
    // Get children indexes
    int l = i * 2;
    int r = l + 1;

    // Get the index of the largest value
    int key;
        // Check left
    if( l <= size && socArray[l - 1].total > socArray[i - 1].total)
        key = l;
        // If not left, force i
    else
        key = i;
        // Check right
    if( r <= size && socArray[r - 1].total > socArray[i - 1].total)
        key = r;

    // Swap heap values of parent and child if necessary, and then max-heapify everything under the swapped child
    if(key != i){
        // Swap values
        SOC temp = socArray[i - 1];
        socArray[i - 1] = socArray[key];
        socArray[key] = temp;

        // MAX_HEAPIFY modified child
        MAX_HEAPIFY(socArray, key, size);
    }

    return 0;   // Successful runtime
}

// Deletes max value from a heap and then calls MAX_HEAPIFY
/*
 * Takes 2 inputs: socArray and size
 * socArray is a pointer to a SOC array
 * size is the number of elements in socArray
 */
int DELETE_MAX(SOC* socArray, int size){
    socArray[0] = socArray[size - 1];           // Copy last element to first, overwriting max
    free(socArray[size - 1]);                   // Remove redundant element
    MAX_HEAPIFY(socArray, 1, size - 1); // Retain max heap property
    int build = BUILD_MAX_HEAP(socArray, size);

    return 0;   // Successful runtime
}

// Turns an array of SOC structures into a max heap
/*
 * Takes 2 inputs: socArray and size.
 * socArray is a pointer to a SOC array
 * size is the number of elements in socArray
 */
int BUILD_MAX_HEAP(SOC* socArray, int size){
    // Turns each element in socArray into a max heap from the last element to the first
    for(int i = size / 2; i >= 1; i--)
        MAX_HEAPIFY(socArray, i, size);

    return 0;   // Successful runtime
}