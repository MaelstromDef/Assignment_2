
// Hello

#include "query.h"
#include "heap.h"
#include <cstring>
#include <iostream>

// Returns the type of query selected from the inputs
query_type get_query(char inputs[NUM_INPUTS][INPUT_LENGTH]){
    // GET QUERY TYPE

    query_type q;

    // find max
    if (strcmp(inputs[0], "find") == 0 && strcmp(inputs[1], "max") == 0)
        q = MAX;
    // find ratio
    else if(strcmp(inputs[0], "find") == 0 && strcmp(inputs[1], "ratio") == 0)
        q = RATIO;
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
void findMax(char workerType[INPUT_LENGTH], int numWorkers, int YYYY){

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

    SOC *socArray;  // Holds a SOC array (memory allocated)
    socArray = getSOC(YYYY);

    if(socArray != NULL) {
        std::cout << "Top " << numWorkers << " occupations in " << YYYY << " for " << workerType << " workers:" << std::endl;

        // Turn socArray into a max heap
        BUILD_MAX_HEAP(socArray, w, NUM_OCC);

        // PRINT N MAX FROM HEAP

        for (int i = 0; i < numWorkers; i++) {
            SOC printMe = DELETE_MAX(socArray, w, NUM_OCC - i);

            std::cout << "\t" << printMe.occupation << ": ";

            switch (w) {
                case male:
                    commaInt(printMe.male);
                    std::cout << std::endl;
                    break;
                case female:
                    commaInt(printMe.female);
                    std::cout << std::endl;
                    break;
                case total:
                    commaInt(printMe.total);
                    std::cout << std::endl;
                    break;
            }
        }

        // DELETE HEAP
        free(socArray);
    }else{
        std::cout << "Query failed." << std::endl;
    }

    std::cout << std::endl;
}

void findRatio(int YYYY, int ZZZZ){
    // Check proper dating
    if(ZZZZ < YYYY) {
        std::cout << "ERROR: YEARS IN WRONG ORDER." << std::endl;
        return;
    }



    // PRINT RESULTS
    std::cout << "The female-to-male earnings ratio for 2018-2019:\n";

    EI = 2019 - YYYY;   // Gets index of last piece

    // Print loop using EI as index
    while(EI <= 2019 - ZZZZ){
        // Get ratio
        float ratio = EArray[EI].female_earnings_moe / EArray[EI].male_earnings;
        int stdPrec = std::cout.precision();
        std::cout.precision(3);

        // Print ratio
        std::cout << "\t" << (2019 - EI) << ": " << ratio << "%" << std::endl;

        // Modify vars
        std::cout.precision(stdPrec);       // Restore cout precision
        EI++;       // Increment earnings array index
    }
}