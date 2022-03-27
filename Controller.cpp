/*
 * Controller.cc is the file that takes input and calls functions in order to properly implement the commands from its input
 */

#include <iostream>
#include "defns.h"
#include "utility.h"
#include "query.h"
#include "bst.h"
#include "hash.h"

int main(int argc, char* argv[]){
    // NECESSARY ELEMENTS
    bst *binTree;                           // Holds a binary search tree
    hash_table_entry** HashTable;           // Holds an array of hash_table_entry pointers.

    HashTable = (hash_table_entry**)malloc(sizeof(hash_table_entry*) * m);
    binTree = createBST(argv[1], HashTable);

    // SIMULATE PROGRAM

    char inputs[NUM_INPUTS][INPUT_LENGTH];  // Holds input values
    char c;                                 // takes input

    // Controller variable - Holds the index of the current query input or -1 if query input is finished.
    int controller[4];
    int result = -1;
    resetController(controller);

    while(std::cin.get(c)){
        // Skip '"'
        if(c == '\"')
            continue;

        // PERFORM QUERY ON NEW LINE
        if(c == '\n') {
            // Ensure break points
            inputs[1][controller[1]] = '\0';
            inputs[2][controller[2]] = '\0';
            inputs[3][controller[3]] = '\0';

            // Get Query Type
            query_type q = get_query(inputs);

            // Perform query
            std::cout << "Query: ";
            for(int i = 0; i <= 3; i++) {
                std::cout << inputs[i];
                if(i < 3)
                    std::cout << " ";
            }
            std::cout << std::endl << std::endl;

            switch(q){
                case MAX: {     // find max
                    int workers = intFromString(inputs[3]);
                    result = findMax(inputs[2], workers, intFromString(argv[1]));
                    break;
                }
                case RATIO: {   // find ratio
                    int startYear = intFromString(inputs[2]);
                    int endYear = intFromString(inputs[3]);
                    result = findRatio(startYear, endYear);
                    break;
                }
                case FIND_OCC:{ // Find Occupation
                    int SocCode = intFromString(inputs[2]);
                    result = findOcc(SocCode, HashTable);
                    break;
                }
                case RANGE_OCC:{    // Rage Occupation
                    result = rangeOcc(inputs[2], inputs[3], -3, binTree);
                    break;
                }
                default:        // Unrecognized Query
                    result = -1;
                    break;
            }

            // Force new input
            inputs[0][1] = '\0';
            q = NA;

             if(result == -2)
                 std::cout << "Occupation with SOC code " << inputs[2] << " not found." << std::endl;

            if(result < 0)
                std::cout << "Query failed." << std::endl << std::endl;
            else
                std::cout << std::endl;

            // Reset the controller before moving on to next instruction
            resetController(controller);
            result = -1;
            continue;
        }

        // ADD CURRENT CHARACTER TO INPUT STRING
        for(int i = 0; i < NUM_INPUTS; i++){
            // While the part of the input is active (controller[i] == -1 when it's inactive)
            if(controller[i] >= 0){

                // Handles over sized index
                if(controller[i] > INPUT_LENGTH){
                    resetController(controller);
                    while(std::cin.get(c) && c != '\n');
                    break;
                }

                // space indicates next part of input
                if(c == ' ') {
                    inputs[i][controller[i]] = '\0';
                    controller[i] = -1;
                }
                // add to current input
                else {
                    inputs[i][controller[i]] = c;
                    controller[i]++;
                }

                // exit for loop
                break;
            }
        }
    }

    // Delete every node in the bst, along with every entry in the HashTable
    deleteBST(binTree, HashTable);
    // Delete the HashTable itself
    free(HashTable);
}