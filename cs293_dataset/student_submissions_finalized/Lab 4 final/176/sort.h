#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "tree.cpp"
#include "choose.cpp"

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
  void getArray();
  int partition(int start, int finish);
  bool pivotPresent(Journey* pivot);
  int Quicksort(int start, int finish); // Sort the array according to the stored values
  int QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  int getComparisons(); // returns the no. of comparisons made
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree() {delete[] array; delete tree;}; // Destructor
};

#endif