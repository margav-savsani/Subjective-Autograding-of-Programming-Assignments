#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "tree.cpp"
#include "journey.cpp"

class SorterTree {
  private:
    Journey* array;
    BST* tree;
    int choice; // Choice of pivot function to use
    int l; // Total number of entries
    int comparisons; // Total number of comparisons performed
    
    void merge(int pivot); // merges array[:pivot+1] and array[pivot+1:] and stores into array

  public:
    SorterTree(int choice, int l); // Define valid constructor
    SorterTree(int choice, Journey* templ, int l); // constructing from templ
    ~SorterTree(); // Destructor
    
    bool Quicksort(int start, int finish); // Sort the array according to the stored values
    bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
    
    bool printArray();
    bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
    
    BST* getTree(); // returns pointer to the tree of pivots
};

#endif
