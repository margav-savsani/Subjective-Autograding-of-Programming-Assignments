#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <fstream>
// #include "tree.cpp"
#include "journey.h" // changed from cpp

class Journey;

class SorterTree
{
private:   
    Journey* array; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
    // BST* tree;
    int choice; // Choice of pivot function to use
    int l; // Total number of entries
    int comparisons; // Total number of comparisons performed
  
public:
    SorterTree(int choice, int l): choice(choice), l(l){}; // Define valid constructor
    void load(std::ifstream &infile);
    bool Quicksort(int start, int finish); // Sort the array according to the stored values
    bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
    bool printArray();
    bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
    // BST* getTree(); // returns pointer to the tree of pivots
    ~SorterTree(){} // Destructor
    Journey *getPivot(int start, int finish) const;
};

#endif