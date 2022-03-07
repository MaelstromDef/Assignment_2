#include <iostream>
#include <cstring>

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
        if((((unsigned char)input[i]) >= '0') && (((unsigned char)input[i]) <= '9')) {
            num *= 10;
            num += (int)((unsigned char)input[i]) - 48;
        }
    }

    return num;
}

// Prints out comma version of an int
void commaInt(int toPrint){
    int log = 0;
    int logDivider = 1;

    // Find log of toPrint
    while(toPrint / logDivider > 0){
        log++;
        logDivider *= 10;
    }

    // Set log and holder back to a point where toPrint / holder > 0 (single digit)
    logDivider /= 10;
    log--;

    /*
     * PRINTING:
     *  Printing must be done in two parts, the first section and then the rest of the int.
     *  This is because the first section can be 1, 2, or 3 digits long before the next comma comes.
     */

    // Print first section of the int, as long as the number is not of standard form
    if(log % 3 != 2) {
        for (int i = log; i % 3 != 2 && i >= 0; i--) {
            std::cout << toPrint / logDivider;
            toPrint -= (toPrint / logDivider) * logDivider;         // Subtract toPrint by its largest digit
            logDivider /= 10;                                       // Take away 1 digit from logDivider
        }

        // Print comma if the number is more than 3 digits, otherwise whole number has been printed.
        if(log > 2)
            std::cout << ",";
        else
            return;
    }

    // Print rest of the int
    while(log >= 0){
        std::cout << toPrint / logDivider;
        toPrint -= (toPrint / logDivider) * logDivider;         // Subtract toPrint by its largest digit

        logDivider /= 10;   // Take a digit away from logDivider
        log--;              // Increment log downwards

        // Print comma before 1st of next 3 digits
        if(log % 3 == 2)
            std::cout << ",";
    }
}

// Gets an array of heap-allocated SOC elements from the SOC_FILE
/*
 * Returns socArray, which is an array of pointers to SOC elements
 */
SOC* getSOC(int YYYY){
    // Create an array of SOC elements using heap allocation
    SOC* socArray;
    socArray = (SOC*) malloc (sizeof(SOC) * NUM_OCC);

    char buffer[OCC_LEN];   // Holds input until ready to use
    char c;                 // Holds immediate character

    // Indexes for socArray and buffer respectively
    int socI = 0;
    int bufI = 0;

    // Create a variable to keep track of current SOC element
    SOC_detail detail = OCC;

    // OPEN SOC FILE

    // Add appropriate ending to soc file name
    strcpy(buffer, SOC_FILE);
    bufI = 1000;
    for(int i = 0; i < 4; i++){
        buffer[20+i] = (YYYY / bufI)+48;
        YYYY -= (YYYY / bufI) * bufI;
        bufI /= 10;
    }

    // Add .csv extension to file name
    buffer[24] = '.';
    buffer[25] = 'c';
    buffer[26] = 's';
    buffer[27] = 'v';
    buffer[28] = '\0';

    bufI = 0;   // reset bufI to 0 after unrelated usage

    std::ifstream socFile;
    socFile.open(buffer);
    if(socFile.is_open()){

        // Skip unnecessary lines
        for(int i = 0; i < 5; i++)
            while(socFile.get(c) && c != '\n');

        // Get necessary lines
        while(socFile.get(c)){

            // INDICATES OUT OF BOUNDS
            if(socI >= NUM_OCC){
                std::cout << "ERROR: SOC OUT OF BOUNDS" << std::endl;
                return NULL;
            }

            // INDICATES NEW SOC ELEMENT
            if(c == '\n'){

                // Enter last of line's information (.male)
                buffer[bufI] = '\0';

                if(strcmp(buffer, "N") == 0){
                    socArray[socI].male = -1;
                }else
                    socArray[socI].male = intFromString(buffer);

                // Update parsing values
                socI++;
                bufI = 0;
                detail = OCC;
                socFile.get(c); // Gets rid of trailing character

                continue; // Next iteration
            }
            // INDICATES NEW SOC DETAIL
            if(c == ','){

                // Enter detail information
                buffer[bufI] = '\0';

                switch(detail){
                    case OCC:
                        strcpy(socArray[socI].occupation, buffer);
                        break;
                    case CODE:
                        strcpy(socArray[socI].SOC_code, buffer);
                        break;
                    case TOTAL:
                        if(strcmp(buffer, "N") == 0){
                            socArray[socI].total = -1;
                        }else
                            socArray[socI].total = intFromString(buffer);
                        break;
                    case FEMALE:
                        if(strcmp(buffer, "N") == 0){
                            socArray[socI].female = -1;
                        }else
                            socArray[socI].female = intFromString(buffer);
                        break;
                }

                // Update parsing values
                bufI = 0;
                detail = (SOC_detail)((int)detail + 1);

                continue; // Next iteration

            }

            // Add to buffer
            buffer[bufI] = c;
            bufI++;
        }

    }else
        return NULL;

    socFile.close();

    return socArray;
}