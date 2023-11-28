#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "tree.cpp"
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
    void Quicksort(int start, int finish); // Sort the array according to the stored values
    void QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
    void printArray();
    bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
    BST* getTree(); // returns pointer to the tree of pivots
    // ~SorterTree(); // Destructor
};

#endif