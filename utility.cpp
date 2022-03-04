#include <iostream>

#include "utility.h"

// Resets int array "controller" values to 0
void resetController(int* controller){
    for(int i = 0; i < 4; i++){
        controller[i] = 0;
    }
}

// Gets an integer from char array "input"
int intFromString(char* input){
    int num = 0;

    for(int i = 0; input[i] != '\0'; i++){
        if((input[i] >= '0') && (input[i] <= '9')) {
            num *= 10;
            num += input[i] - 48;
        }
    }
}

// Prints out comma version of an int
void commaInt(int toPrint){
    int log = 0;
    int holder = 1;

    // Find log of toPrint
    while(toPrint / holder > 0){
        log++;
        holder *= 10;
    }

    // Set log and holder back to a point where toPrint / holder > 0 (single digit)
    holder /= 10;
    log--;

    /*
     * PRINTING:
     *  Printing must be done in two parts, the first section and then the rest of the int.
     *  This is because the first section can be 1, 2, or 3 digits long before the next comma comes.
     */

    // Print first section of the int
    for(int i = log; i % 3 != 0; i--){
        std::cout << toPrint / holder;
        toPrint -= (toPrint / holder) * holder;         // Subtract toPrint by its largest digit
        holder /= 10;
        log--;
    }

    // Print rest of the int
    while(log > 0){
        if(log % 3 == 0)
            std::cout << ",";

        std::cout << toPrint / holder;
        toPrint -= (toPrint / holder) * holder;         // Subtract toPrint by its largest digit

        holder /= 10;
        log--;
    }
}

// Gets an array of heap-allocated SOC elements from the SOC_FILE
/*
 * Returns socArray, which is an array of pointers to SOC elements
 */
SOC** getSOC(){
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