/*
 * Controller.cc is the file that takes input and calls functions in order to properly implement the commands from its input
 */

#include <iostream>
#include <cstring>
#include "defns.h"
#include "utility.h"
#include "query.h"

int main(int argc, char* argv[]){
    // SIMULATE PROGRAM

    // Takes queries
    char inputs[4][6];
    char c;

    // Controller variable
    int controller[4];
    resetController(controller);

    while(std::cin.get(c)){
        // Performs query depending on input line
        if(c == '\n') {
            query(inputs);
            resetController(controller);
            continue;
        }

        // Finds where to add "c" onto
        for(int i = 0; i < 4; i++){
            if(controller[i] >= 0){

                if(c == ' ') {
                    inputs[i][controller[i]] = '\0';
                    controller[i] = -1;
                }
                else {
                    inputs[i][controller[i]] = c;
                    controller[i]++;
                }
            }
        }
    }
}