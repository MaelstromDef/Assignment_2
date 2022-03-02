/*
 * utility.cc handles all the utility functions for the Assignment 2 CSE310 project
 */

#include "../HeaderFiles/utility.h"

// Resets int array "controller" values to 0
void resetController(int* controller){
    for(int i = 0; i < 4; i++){
        controller[i] = 0;
    }
}

// Gets an integer from char array "input"
int intFromString(char input[INPUT_LENGTH]){
    int num = 0;

    for(int i = 0; i < INPUT_LENGTH && input[i] != '\0'; i++){
        num *= 10;
        num += input[i] - 48;
    }
}

// Gets an array of heap-allocated SOC elements from the SOC_FILE
/*
 * Returns socArray, which is an array of pointers to SOC elements
 */
SOC** getSOC(SOC* socArray[NUM_OCC], worker_type w){
    // INITIALIZE VARS
    char c;             // char to hold file stream's input
    int i = 0;          // holds current index of socArray
    int in_line = 0;    // holds number of characters read from the current line

    socArray[i] = (SOC*) malloc (sizeof(SOC));  // Initialize socArray

    // Open csv file containing relevant info
    std::ifstream socFile;
    socFile.open(SOC_FILE);

    // PARSE ARRAY

    // Skip unnecessary lines
    for(int i = 0; i < 5; i++){
        char buffer[255];
        socFile.getline(buffer, 256);
    }

    // Get SOC elements
    while(socFile.get(c)){
        // Next element
        if(c == '\n'){
            i++;
            in_line = 0;
            socArray[i] = (SOC*) malloc (sizeof(SOC));
        }

        // ENTER INFORMATION

        // Enter occupation
        if(in_line < OCC_LEN){

        }
        // Enter SOC-code
        else if(in_line < OCC_LEN + CODE_LEN){

        }
        // Enter total, female, and male
        else{

        }
    }

    return socArray;
}