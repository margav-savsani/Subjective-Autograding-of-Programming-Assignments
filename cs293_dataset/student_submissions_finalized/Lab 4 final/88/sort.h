#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  void printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(){delete[] array; delete tree;} // Destructor

  void myswap(int idx1, int idx2); // swaps two elements of array
  int getcomparisions(){return comparisons;} // returns total number of comparision operators done
  int getimbalance(){return tree->getImbalance();} // returns the value of imbalance of BST
  void printTree(){return tree->printBST("");} // prints the BST in readable format
};

#endif
