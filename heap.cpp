/*
 * heap.cc handles all heap functions for the Assignment 2 CSE310 project
 */

#include "heap.h"
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
int MAX_HEAPIFY(SOC* socArray, worker_type w, int i, int size){
    // Get children indexes
    int l = i * 2;
    int r = l + 1;

    // Get the index of the largest value
    int key;

    switch(w) {
        case total:
            // Check left
            if (l <= size && socArray[l - 1].total > socArray[i - 1].total)
                key = l;
                // If not left, force i
            else
                key = i;
            // Check right, and if right force
            if (r <= size && socArray[r - 1].total > socArray[key - 1].total)
                key = r;
            break;
        case female:
            // Check left
            if (l <= size && socArray[l - 1].female > socArray[i - 1].female)
                key = l;
                // If not left, force i
            else
                key = i;
            // Check right, and if right force
            if (r <= size && socArray[r - 1].female > socArray[key - 1].female)
                key = r;
            break;
        case male:
            // Check left
            if (l <= size && socArray[l - 1].male > socArray[i - 1].male)
                key = l;
                // If not left, force i
            else
                key = i;
            // Check right, and if right force
            if (r <= size && socArray[r - 1].male > socArray[key - 1].male)
                key = r;
            break;
    }

    // Swap heap values of parent and child if necessary, and then max-heapify everything under the swapped child
    if(key != i){
        // Swap values
        SOC temp = socArray[i - 1];
        socArray[i - 1] = socArray[key - 1];
        socArray[key - 1] = temp;

        // MAX_HEAPIFY modified child
        MAX_HEAPIFY(socArray, w, key, size);
    }

    return 0;   // Successful runtime
}

// Deletes max value from a heap and then calls MAX_HEAPIFY
/*
 * Takes 2 inputs: socArray and size
 * socArray is a pointer to a SOC array
 * size is the number of elements in socArray
 */
SOC DELETE_MAX(SOC* socArray, worker_type w, int size){
    SOC max = socArray[0];
    socArray[0] = socArray[size - 1];           // Copy last element to first, overwriting max
    MAX_HEAPIFY(socArray, w, 1, size - 1); // Retain max heap property

    return max;   // Successful runtime
}

// Turns an array of SOC structures into a max heap
/*
 * Takes 2 inputs: socArray and size.
 * socArray is a pointer to a SOC array
 * size is the number of elements in socArray
 */
int BUILD_MAX_HEAP(SOC* socArray, worker_type w, int size){
    // Turns each element in socArray into a max heap from the last element to the first
    for(int i = size / 2; i >= 1; i--)
        MAX_HEAPIFY(socArray, w, i, size);

    return 0;   // Successful runtime
}