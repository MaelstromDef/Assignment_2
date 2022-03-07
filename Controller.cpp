/*
 * Controller.cc is the file that takes input and calls functions in order to properly implement the commands from its input
 */

#include <iostream>
#include "defns.h"
#include "utility.h"
#include "query.h"

int main(int argc, char* argv[]){
    // SIMULATE PROGRAM

    char inputs[NUM_INPUTS][INPUT_LENGTH];  // Holds input values
    char c;                                 // takes input

    // Controller variable - Holds the index of the current query input or -1 if query input is finished.
    int controller[4];
    resetController(controller);

    while(std::cin.get(c)){
        // PERFORM QUERY ON NEW LINE
        if(c == '\n') {
            // Ensure break point
            inputs[3][controller[3]] = '\0';

            // Get Query Type
            query_type q = get_query(inputs);

            // Perform query
            switch(q){
                case MAX: {     // find max
                    int workers = intFromString(inputs[3]);
                    findMax(inputs[2], workers, intFromString(argv[1]));
                    // Force new input
                    inputs[0][1] = '\0';
                    q = NA;
                    break;
                }
                case RATIO: {   // find ratio
                    int startYear = intFromString(inputs[2]);
                    int endYear = intFromString(inputs[3]);
                    findRatio(startYear, endYear);
                    // Force new input
                    inputs[0][1] = '\0';
                    q = NA;
                    break;
                }
                default:        // Unrecognized Query
                    std::cout << "Query failed." << std::endl;
                    break;
            }

            // Reset the controller before moving on to next instruction
            resetController(controller);
            continue;
        }

        // ADD CURRENT CHARACTER TO INPUT STRING
        for(int i = 0; i < NUM_INPUTS; i++){
            // While the part of the input is active (controller[i] == -1 when it's inactive)
            if(controller[i] >= 0){

                // Handles over sized index
                if(controller[i] > INPUT_LENGTH){
                    std::cout << "OVER SIZED INPUT AT: " << i << std::endl;
                    resetController(controller);
                    return -1;
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
}