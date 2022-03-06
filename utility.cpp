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
SOC* getSOC(){
    // INITIALIZE VARS
    char c;                 // char to hold file stream's input
    char buffer[OCC_LEN];   // Holds string-type inputs
    int buffer_index = 0;
    int i = 0;              // holds current index of socArray
    SOC_detail detail = OCC;    // holds number of characters read from the current line

    SOC *socArray;
    socArray = (SOC*) malloc (sizeof(SOC) * OCC_LEN);  // Initialize socArray

    // Open csv file containing relevant info
    std::ifstream socFile;
    socFile.open(SOC_FILE);

    // PARSE ARRAY

    // Overlook 5 lines
    for(i = 0; i < 5; i++)
        while(socFile.get(c) && c != '\n');

    // Get SOC elements
    while(socFile.get(c)){

        // Look for data separators
        if(c == '\n'){  // Next element
            i++;
            detail = OCC;
            socFile.get(c);     // Get next usable

        }else if(c == ','){     // Next data type

            // Update buffer values
            if(buffer_index < OCC_LEN)
                buffer[buffer_index] = '\0';
            buffer_index = 0;

            // Update current data type of socArray[i]
            switch(detail){
                case OCC:
                    // Copy buffer to socArray value
                    while(buffer[buffer_index] != '\0' && buffer_index < OCC_LEN){
                        socArray[i].occupation[buffer_index] = buffer[buffer_index];
                        buffer_index++;
                    }
                    buffer_index = 0;
                    break;
                case CODE:
                    // Copy buffer to socArray value
                    while(buffer[buffer_index] != '\0' && buffer_index < OCC_LEN){
                        socArray[i].SOC_code[buffer_index] = buffer[buffer_index];
                        buffer_index++;
                    }
                    buffer_index = 0;
                    break;
                case TOTAL:
                    socArray[i].total = intFromString(buffer);
                    break;
                case FEMALE:
                    socArray[i].female = intFromString(buffer);
                    break;
                case MALE:
                    socArray[i].male = intFromString(buffer);
                    break;
            }

            // Go to next data type
            detail = (SOC_detail)((int)detail +  1);         // Change SOC_detail to next type
            socFile.get(c);     // Get next usable
        }

        // Increment buffer values
        buffer[buffer_index] = c;
        buffer_index++;
    }

    // Indicate an empty node if all nodes weren't used
    if(buffer_index < OCC_LEN)
        socArray[buffer_index].total = 0;

    socFile.close();

    return socArray;
}