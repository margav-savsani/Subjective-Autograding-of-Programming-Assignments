#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "tree.cpp"
#include "journey.cpp"

class SorterTree
{
private:   
  
  //int* codes; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  Journey* array;
  BST* tree;
  SorterTree(int choice, int l); // Define valid constructor
  int Quicksort_partition(int start, int finish);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  void Quicksort_new();
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  void QuicksortWithBSTInsert_new();
  int Quicksort_partition_BST(int start, int finish);
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  int getComparisons();
  int getImbalance() {return tree->getImbalance();}
  ~SorterTree(); // Destructor
};
#endif