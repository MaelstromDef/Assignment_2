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

// Prints out comma version of an int (Does not print to newline)
void commaInt(int toPrint){
    int buffer[10];
    int i = 0;

    // Put the integer to print into a buffer backwards
    while(toPrint > 0){
        buffer[i] = toPrint % 10;
        toPrint /= 10;
        i++;
    }

    i--;

    // Print the integer
    while(i >= 0){
        std::cout << buffer[i];
        if(i % 3 == 0 && i != 0)
            std::cout << ",";
        i--;
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
    bool commaBlock = false;     // At 0, commaBlock does nothing. At 1, commaBlock prevents commas from being seperators

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

            // swap commaBlock's value upon finding a quotation mark
            if(c == '\"') {
                commaBlock = !commaBlock;
                continue;
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


                continue; // Next iteration
            }
            // INDICATES NEW SOC DETAIL
            if(c == ',' && !commaBlock){

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
                        }else{
                            socArray[socI].total = intFromString(buffer);
                        }
                        break;
                    case FEMALE:
                        if(strcmp(buffer, "N") == 0){
                            socArray[socI].female = -1;
                        }else {
                            socArray[socI].female = intFromString(buffer);
                        }
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