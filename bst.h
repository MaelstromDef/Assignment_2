//
// Created by cse310 on 3/25/22.
//

#ifndef ASSIGNMENT_2_BST_H
#define ASSIGNMENT_2_BST_H

#include "defns.h"

// Create a bst from the Occupation-Dist-All-YYYY.csv file
bst* createBST(char* YYYY, hash_table_entry** HashTable);

// Delete a bst
void deleteBST(bst* binTree, hash_table_entry** HashTable);

#endif //ASSIGNMENT_2_BST_H
