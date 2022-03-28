//
// Created by cse310 on 3/25/22.
//

#include "bst.h"
#include "utility.h"
#include "hash.h"
#include <cstring>
#include <iostream>

/*
int numNodes = 0;
int height =  0;
int heightL = 0;
int heightR = 0;
int tempHeight = 0;
int dir = -1;
 */

// Creates a leaf node for the bst being created in createBST. This leaf is created at the end
// of a chain, the path of which is determined lexicographically
bst* createLeaf(bst* node, SOC soc){
    // Put into a right node
    if(strcmp(node->soc.occupation, soc.occupation) < 0){
        if(node->right != NULL) {
            //if(dir == -1)
            //    dir == 1;
            //tempHeight++;
            createLeaf(node->right, soc);
        }else{
            node->right = (bst*) malloc(sizeof(bst));
            node = node->right;

            node->soc = soc;
            node->left = NULL;
            node->right = NULL;
            return node;
        }
    }
    // Put into a left node
    else{
        if(node->left != NULL) {
            //if(dir == -1)
            //    dir = 0;
            //tempHeight++;
            createLeaf(node->left, soc);
        }else{
            node->left = (bst*) malloc(sizeof(bst));
            node = node->left;

            node->soc = soc;
            node->left = NULL;
            node->right = NULL;
            return node;
        }
    }
}

// Creates a bst given some Occupation-Dist-All-YYYY.csv file by parsing the socs given in the
// file and creating a bst node for each of them
bst* createBST(char* YYYY, hash_table_entry** HashTable){
    // Get an array of soc elements
    SOC* socArr = getSOC(intFromString(YYYY));

    // Declare variables
    bst* root;
    root = (bst*) malloc (sizeof(bst));

    //numNodes++;
    //heightL++;
    //heightR++;

    // Copy first node into tree
    root->soc = socArr[0];
    root->left = NULL;
    root->right = NULL;
    createHashEntry(root, HashTable);

    // Create a bst node for each soc in the socArr
    for(int i = 1; i < NUM_OCC; i++){
        bst *temp = createLeaf(root, socArr[i]);

        /*
        if(dir == 0 && tempHeight > heightL)
            heightL = tempHeight;
        else if(dir == 1 && tempHeight > heightR)
            heightR = tempHeight;
        tempHeight = 1;
        numNodes++;
         */

        createHashEntry(temp, HashTable);
    }

    /*
    // Print experimental values
    if(heightL > height)
        height = heightL;
    if(heightR > height)
        height = heightR;

    std::cout << "BINARY SEARCH TREE VALUES" << std::endl;
    std::cout << "\tNumber of Nodes: " << numNodes << std::endl;
    std::cout << "\tHeight: " << height << std::endl;
    std::cout << "\tHeight of Left: " << heightL << std::endl;
    std::cout << "\tHeight of Right: " << heightR << std::endl << std::endl;
    */

    free(socArr);
    return root;
}

// Recursively Deletes a bst from the children to the root
void deleteBST(bst* node, hash_table_entry** HashTable){
    // Delete Children
    if(node->left != NULL)
        deleteBST(node->left, HashTable);
    if(node->right != NULL)
        deleteBST(node->right, HashTable);

    // Delete associated hash entries
    deleteHashEntry(node, HashTable);
    // Delete current node
    free(node);
}