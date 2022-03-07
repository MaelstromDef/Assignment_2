
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

    SOC *socArray;  // Holds an SOC array (memory allocated)
    socArray = getSOC(YYYY);

    if(socArray != NULL) {
        std::cout << "Query: find max " << workerType << " " << numWorkers << "\n" << std::endl;
        std::cout << "Top " << numWorkers << " occupations in " << YYYY << " for " << workerType << " workers:" << std::endl;

        // Turn socArray into a max heap
        BUILD_MAX_HEAP(socArray, w, NUM_OCC);

        // PRINT N MAX FROM HEAP

        for (int i = 0; i < numWorkers; i++) {
            SOC printMe = DELETE_MAX(socArray, w, NUM_OCC);

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

    // Open earnings file and skip unnecessary lines
    char c;
    std::ifstream earningsFile;
    earningsFile.open(EARNINGS_FILE);

    if(!(earningsFile.is_open())){
        std::cout << "ERROR: EARNINGS FILE NOT OPENED" << std::endl;
    }

    for(int i = 0; i < 8; i++){
        // Ignore line
        while(earningsFile.get(c) && c != '\n');
    }

    // Create and fill earnings array
    earnings EArray[70];        // array of earnings structures with a max size = the amount of years possible in earnings file
    int EI = 0;                 // index for EArray
    char buffer[20];            // Holds current piece of the earnings line
    int BI = 0;                 // index for buffer
    earnings_detail e = year;   // Keeps track of what detail is being looked at

    while(earningsFile.get(c)){
        if(EI >= 70){
            std::cout << "ERROR: TOO MANY EARNINGS ELEMENTS" << std::endl;
            return;
        }
        if(BI >= 20){
            std::cout << "ERROR: BUFFER UNDERSIZED" << std::endl;
            return;
        }

        // NEW LINE
        if(c == '\n'){
            buffer[BI] = '\0';      // Ensure break point
            EArray[EI].female_earnings_moe = intFromString(buffer);

            EI++;                   // Next earnings element
            BI = 0;                 // Reset buffer
            e = year;               // Reset detail
            earningsFile.get(c);    // Automatically go to next character
        }

        // END OF FIELD
        if(c == ','){
            buffer[BI] = '\0';      // Ensure break point

            // Update correct field
            switch(e){
                case year:
                    EArray[EI].year = intFromString(buffer);
                    break;
                case MT:
                    EArray[EI].male_total = intFromString(buffer);
                    break;
                case MWE:
                    EArray[EI].male_with_earnings = intFromString(buffer);
                    break;
                case ME:
                    EArray[EI].male_earnings = intFromString(buffer);
                    break;
                case MMOE:
                    EArray[EI].male_earnings_moe = intFromString(buffer);
                    break;
                case FT:
                    EArray[EI].female_total = intFromString(buffer);
                    break;
                case FWE:
                    EArray[EI].female_with_earnings = intFromString(buffer);
                    break;
                case FE:
                    EArray[EI].female_earnings = intFromString(buffer);
                    break;
            }

            e = (earnings_detail)((int) e + 1);     // Update earnings_detail looked at
            BI = 0;                                 // Reset buffer
            earningsFile.get(c);                    // Automatically go to next character
        }

        buffer[BI] = c; // Update buffer
        BI++;           // Increment buffer index
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