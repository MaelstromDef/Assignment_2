/*
 * query.cc is a c++ file that handles the query functions called in Controller.cc
 */

#include "../HeaderFiles/query.h"
#include "../HeaderFiles/heap.h"
#include <cstring>
#include <iostream>

// Returns the type of query selected from the inputs
query_type get_query(char inputs[NUM_INPUTS][INPUT_LENGTH]){
    // GET QUERY TYPE

    query_type q;

    // find max
    if (strcmp(inputs[0], "find") == 0 && strcmp(inputs[1], "max") == 0)
        q = max;
    // find ratio
    else if(strcmp(inputs[0], "find") == 0 && strcmp(inputs[1], "ratio") == 0)
        q = ratio;
    // Query Type Unknown
    else
        q = NA;

    return q;   // Successful Runtime
}

// Performs the "find max" function
/*
 * Takes 2 inputs: workerType and numWorkers.
 * workerType is a string that holds "male", "female", or "total", which represents the types of workers being looked at
 * numWorkers is an int that represents the amount of workers to be displayed.
 */
void findMax(char workerType[INPUT_LENGTH], int numWorkers){
    // Get type of worker to find
    worker_type w;
    if(strcmp(workerType, "male") == 0)
        w = male;
    else if(strcmp(workerType, "female") == 0)
        w = female;
    else if(strcmp(workerType, "total") == 0)
        w = total;
    else{
        std::cout << "UNRECOGNIZED WORKER TYPE: " << workerType << std::endl;
        return;
    }

    // CREATE HEAP FROM SOC FILE

    SOC **socArray;  // Holds an SOC array (memory allocated)
    socArray = getSOC();

    // Get size of the array
    int size = -1;
    for(int i = 0; i < NUM_OCC; i++){
        if(socArray[i]->total == -1){
            size = i;
            break;
        }
    }

    // Entire socArray was used
    if(size == -1)
        size = NUM_OCC - 1;

    // Turn socArray into a max heap
    BUILD_MAX_HEAP(socArray,size);

    // PRINT N MAX FROM HEAP
    for(int i = 0; i < numWorkers; i++) {
        SOC *printMe = DELETE_MAX(socArray, size);
        std::cout << "\t" << printMe.occupation << ": ";

        switch(w){
            case male:
                commaInt(printMe->male);
                std::cout << std::endl;
                break;
            case female:
                commaInt(printMe->female);
                std::cout << std::endl;
                break;
            case total:
                commaInt(printMe->total);
                std::cout << std::endl;
                break;
            default:
                std::cout << "ERROR WITH WORKER TYPE" << std::endl;
                i = numWorkers;
                break;
        }
    }

    // DELETE HEAP
    for(int i = size - 1; i >= 0; i--){
        free(socArray[i]);
    }
}