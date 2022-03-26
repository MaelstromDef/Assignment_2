//
// Created by cse310 on 3/25/22.
//

#include "bst.h"
#include "utility.h"
#include "hash.h"
#include <cstring>

bst* createLeaf(bst* node, SOC soc){
    // Put into a right node
    if(strcmp(node->soc.occupation, soc.occupation) < 0){
        if(node->right != NULL)
            createLeaf(node->right, soc);
        else{
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
        if(node->left != NULL)
            createLeaf(node->left, soc);
        else{
            node->left = (bst*) malloc(sizeof(bst));
            node = node->left;

            node->soc = soc;
            node->left = NULL;
            node->right = NULL;
            return node;
        }
    }
}

bst* createBST(char* YYYY, hash_table_entry** HashTable){
    // Get an array of soc elements
    SOC* socArr = getSOC(intFromString(YYYY));

    // Declare variables
    bst* root;
    root = (bst*) malloc (sizeof(bst));

    // Copy first node into tree
    root->soc = socArr[0];
    createHashEntry(root);

    // Create a bst node for each soc in the socArr
    for(int i = 0; i < NUM_OCC; i++){
        bst *temp = createLeaf(root, socArr[i]);
        createHashEntry(temp);
    }

    free(socArr);
    return root;
}