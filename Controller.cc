/*
 * Controller.cc is the file that takes input and calls functions in order to properly implement the commands from its input
 */

#include <iostream>
#include "defns.h"
#include "utility.h"
#include "query.h"

int main(int argc, char* argv[]){
    // SIMULATE PROGRAM

    // Takes queries
    char inputs[NUM_INPUTS][INPUT_LENGTH];
    char c;

    // Controller variable
    int controller[4];
    resetController(controller);

    while(std::cin.get(c)){
        // PERFORM QUERY
        if(c == '\n') {
            // Get Query Type
            query_type q = get_query(inputs);

            // Perform query
            switch(q){
                case max: {     // find max
                    int n = intFromString(inputs[3]);
                    findMax(inputs[2], n);
                    break;
                }
                case ratio: {   // find ratio
                    int startYear = intFromString(inputs[2]);
                    int endYear = intFromString(inputs[3]);
                    findRatio(startYear, endYear);
                    break;
                }
                default:        // Unrecognized Query
                    std::cout << "QUERY NOT RECOGNIZED" << std::endl;
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