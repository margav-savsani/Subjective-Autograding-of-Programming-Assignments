#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:
  Journey *array;
  BST *tree;
  int choice;      // Choice of pivot function to use
  int l;           // Total number of entries
  int comparisons; // Total number of comparisons performed

public:
  SorterTree( int choice, int l); 
  SorterTree(Journey *a, int choice, int l); // Define valid constructor
  int partition(Journey *array, int start, int end);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool findMyPivot(Journey *array, int start, int finish, Journey *pivot);
  void myQuicksortWithBSTInsert(BST *A, int start, int finish); // May need extra parameters depending on implementation
  bool QuicksortWithBSTInsert(int start, int finish);           // May need extra parameters depending on implementation
  bool printArray();
  int getComparisons();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST *getTree();                               // returns pointer to the tree of pivots
  ~SorterTree();                                // Destructor
};
