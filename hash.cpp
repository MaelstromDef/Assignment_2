//
// Created by cse310 on 3/25/22.
//

#include "hash.h"
#include "utility.h"
#include <cstring>
#include <iostream>

// Returns the index of a soc code k
int h(int k){
    return k % m;
}

// Creates hash entries for every soc code found in the bst's soc element
void createHashEntry(bst* node, hash_table_entry** HashTable){
    char buffer[8];         // Holds individual soc codes
    SOC temp = node->soc;   // Created for ease of use
    int socI = 0;           // Holds the index for the current part of temp's socCode

    // Parse through the SOC_code field for soc codes and add a hash entry for each of them
    while(temp.SOC_code[socI] != '\0' && socI < CODE_LEN){

        // Get a SOC code
        for(int i = 0; i < 7; i++){
            buffer[i] = temp.SOC_code[socI];
            socI++;
        }

        buffer[7] = '\0';
        int soccode = intFromString(buffer);

        // Create HashTable entry
        hash_table_entry* newEntry;
        newEntry = (hash_table_entry*)malloc(sizeof(hash_table_entry));
        strcpy(newEntry->SOC_code, buffer);
        newEntry->node = node;
        newEntry->next = NULL;

        // Add newEntry to HashTable
        if(HashTable[h(soccode)] == NULL)
            HashTable[h(soccode)] = newEntry;
        else{
            hash_table_entry* inTable = HashTable[h(soccode)];

            // Find next open slot and place newEntry there
            while(inTable->next != NULL)
                inTable = inTable->next;
            inTable->next = newEntry;
        }

        // Go to next SOC_code (finds next digit or end of SOC_code)
        while(temp.SOC_code[socI] != '\0' && socI < CODE_LEN && (temp.SOC_code[socI] > '9' || temp.SOC_code[socI] < '0'))
            socI++;
    }
}

// Deletes hash entries for every soc code found in the bst node's soc element
void deleteHashEntry(bst* node, hash_table_entry** HashTable){
    char buffer[8];         // Holds individual soc codes
    SOC temp = node->soc;   // Created for ease of use
    int socI = 0;           // Holds the index for the current part of temp's socCode

    // Parse through the SOC_code field for soc codes and delete a hash entry for each of them
    while(temp.SOC_code[socI] != '\0' && socI < CODE_LEN){

        // Get a SOC code
        for(int i = 0; i < 7; i++){
            buffer[i] = temp.SOC_code[socI];
            socI++;
        }

        buffer[7] = '\0';
        int soccode = intFromString(buffer);

        // delete entry from HashTable
        if(HashTable[h(soccode)]->node == node){    // Node to delete is the first in chain

            // Node to delete is the only one in chain
            if(HashTable[h(soccode)]->next == NULL)
                free(HashTable[h(soccode)]);
            // Node to delete is not the only one in chain
            else{
                hash_table_entry* toDelete = HashTable[h(soccode)]; // Create pointer to entry to delete
                HashTable[h(soccode)] = toDelete->next;             // Change HashTable pointer to the next entry
                free(toDelete);                                    // Delete entry to delete
            }
        }else{      // Node to delete is not first in chain
            hash_table_entry* entryParser = HashTable[h(soccode)];

            // Go through chain until the entry to delete is found
            while(entryParser->next->node != node)
                entryParser = entryParser->next;

            // Delete entry
            hash_table_entry* toDelete = entryParser->next;
            entryParser->next = toDelete->next;
            free(toDelete);
        }

        // Go to next SOC_code (finds next digit or end of SOC_code)
        while(temp.SOC_code[socI] != '\0' && socI < CODE_LEN && (temp.SOC_code[socI] > '9' || temp.SOC_code[socI] < '0'))
            socI++;
    }
}

// Prints hash entry information
void printHashEntry(hash_table_entry* HashEntry){
    std::cout << "The occupation with SOC code " << HashEntry->SOC_code << std::endl;

    // Print information
    SOC toPrint = HashEntry->node->soc;
    printSoc(toPrint);
}