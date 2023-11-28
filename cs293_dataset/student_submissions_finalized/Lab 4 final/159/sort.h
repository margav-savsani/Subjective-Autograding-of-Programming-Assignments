#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "tree.cpp"
#include "journey.h"

class SorterTree
{
private:   
  Journey* array;
  //int* codes; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  void insert(int j,int p,int idx);
  void Quicksort(int start, int finish); // Sort the array according to the stored values
  void QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  void printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  void getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
#endif