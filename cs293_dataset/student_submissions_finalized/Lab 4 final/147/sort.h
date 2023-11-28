#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <fstream>
#include "tree.cpp"
#include "journey.h" // changed from cpp

class SorterTree {
private:   
    Journey* array; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
    BST* tree;
    int choice; // Choice of pivot function to use
    int l; // Total number of entries. l for length.
    // int comparisons; // Total number of comparisons performed
  
public:
    SorterTree(int choice, int l): choice(choice), l(l), array(nullptr), tree(new BST){};
    ~SorterTree(){ delete array; delete tree; } // Destructor

    void load(std::ifstream &infile);
    
    Journey *getPivot(int start, int finish) const;
    bool Quicksort(int start, int finish); // Sort the array according to the stored values
    bool Quicksort(){ 
        Journey::resetComparisons();
        return Quicksort(0, l-1); 
    }
    bool QuicksortWithBSTInsert(int start, int finish, TreeNode *parent, bool left);
    bool QuicksortWithBSTInsert(){
        Journey::resetComparisons();
        return QuicksortWithBSTInsert(0, l - 1, nullptr, true); 
    }
    
    void printArray() const;
    void printBST() const;
    int getNumComparisons() const;
    void writeToConsole(Journey *pivot, int start, int finish) const;
    
    BST* getTree() const{ return tree; } // returns pointer to the tree of pivots
    int getTreeImbalance() const{ return tree->getImbalance(); }
};

#endif