
// Hello

#include "query.h"
#include "heap.h"
#include "hash.h"
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
    // find occupation
    else if(strcmp(inputs[0], "find") == 0 && strcmp(inputs[1], "occupation") == 0)
        q = FIND_OCC;
    // range occupation
    else if(strcmp(inputs[0], "range") == 0 && strcmp(inputs[1], "occupation") == 0)
        q = RANGE_OCC;
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
int findMax(char workerType[INPUT_LENGTH], int numWorkers, int YYYY){

    // Get type of worker to find
    worker_type w;
    if(strcmp(workerType, "male") == 0)
        w = male;
    else if(strcmp(workerType, "female") == 0)
        w = female;
    else if(strcmp(workerType, "total") == 0)
        w = total;
    else
        return -1;

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
    }else
        return -1;

    return 0;
}

//  Performs the "find range" function
/*
 * Takes 2 inputs: YYYY and ZZZZ
 * YYYY is the starting year of ratios to find and print
 * ZZZZ is the ending year of ratios to find and print
 */
int findRatio(int YYYY, int ZZZZ){
    // Check proper dating
    if(ZZZZ < YYYY)
        return -1;

    earnings* EArray = getEarnings(YYYY,ZZZZ);   // Get array of earnings from earnings file
    if(EArray == NULL)
        return -1;

    // PRINT RESULTS
    std::cout << "The female-to-male earnings ratio for " << YYYY << "-" << ZZZZ << ":\n";

    // Update precision (keep old precision saved)
    int stdPrec = std::cout.precision();
    std::cout.setf(std::ios::fixed);
    std::cout.precision(1);

    // Get the ratio for each necessary year and print it out
    for(int i = 0; i <= (ZZZZ - YYYY); i++){
        double ratio = (double)(EArray[2019 - YYYY + i].female_earnings) / (double)(EArray[2019 - YYYY + i].male_earnings) * 100;
        std::cout << "\t" << (YYYY + i) << ": " << ratio << "%" << std::endl;
    }

    // Reset memory and values
    std::cout.precision(stdPrec);       // Restore cout precision
    std::cout.unsetf(std::ios::fixed);  // Restore formatting
    free(EArray);

    return 0;
}

// Performs the "find occupation" function
/*
 * Takes 2 inputs: socCode and HashTable
 * socCode is the int version of the socCode to find in the HashTable
 * HashTable is a given hash table of hash_table_entry pointers
 */
int findOcc(int socCode, hash_table_entry** HashTable){
    // socCode entered does not have a corresponding place in the HashTable
    if(HashTable[h(socCode)] == NULL)
        return -1;

    // FIND HASH ENTRY
    hash_table_entry* hashEntry = HashTable[h(socCode)];

    // Parse through the chain until hashEntry is the desired entry
    while(intFromString(hashEntry->SOC_code) != socCode){
        // There is not a next entry
        if(hashEntry->next == NULL)
            return -2;

        // Go to next entry
        hashEntry = hashEntry->next;
    }

    // Print entry information
    printHashEntry(hashEntry);

    return 0;
}

// Performs the "range occupation" function.
// Does this recursively by going through the children and printing necessary nodes.
// If successfully finds nodes to print, returns 0. Otherwise, returns -3.
/*
 * Takes 4 inputs: low, high, printed and root.
 * low is a string with the low-bounds on occupations to print.
 * high is a string with the high-bounds on occupations to print.
 * printed is a neg int if nothing's been printed in the recursive calls, and is 0 otherwise.
 * root is the bst to search in.
 */
int rangeOcc(char* low, char* high, int printed, bst* root){
    // Find nodes to print in the left children
    if(strcmp(low, root->soc.occupation) < 0 && root->left != NULL){
        // If nothing's been printed yet, let printed be modified by the rangeOcc return
        if(printed == -3)
            printed = rangeOcc(low, high, printed, root->left);
        else
            rangeOcc(low, high, printed, root->left);
    }

    // Check if current node is something to print
    if(strcmp(low, root->soc.occupation) < 0 && strcmp(root->soc.occupation, high) < 0){
        // Print out first line of query if nothing's been printed yet
        if(printed < 0)
            std::cout << "The occupations in the range \"" << low << "\" to \"" << high << "\":" << std::endl;

        printed = 0;
        printSoc(root->soc);
    }

    // Find nodes to print in the right children
    if(strcmp(root->soc.occupation, high) < 0 && root->right != NULL){
        // If nothing's been printed yet, let printed be modified by the rangeOcc return
        if(printed == -3)
            printed = rangeOcc(low, high, printed, root->right);
        else
            rangeOcc(low, high, printed, root->right);
    }

    return printed;
}