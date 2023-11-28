#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <bits/stdc++.h>
#include "tree.h"
#include "journey.h"
#include "choose.h"

class SorterTree {
private:   
    Journey* array;
    BST* tree;
    std::function<Journey*(Journey*, int, int)> choice; // Choice of pivot function to use
    int sz; // Total number of entries
    int comparisons; // Total number of comparisons performed
  
public:
    SorterTree(int ch, int n, Journey a[]); // Define valid constructor
    int partition(Journey* pivot, int start, int finish);
    bool Quicksort(int start, int finish, int k=1); // Sort the array according to the stored values
    bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
    int comp();  // Returns the number of comparisons in sorting the array
    int imbalance();  // Returns the imbalance of the tree of pivots
    void printArray();
    void printTree();
    // ~SorterTree(); // Destructor
};

#endif