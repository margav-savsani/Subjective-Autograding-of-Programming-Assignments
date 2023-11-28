#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "BST.cpp"
#include "choose.cpp"

class SorterTree
{
private:   
  int* codes; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  BST* tree;
  Journey* array;
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish, int &comp); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish, int &comp); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  int imbalance();//returns imbalance of the tree
  ~SorterTree(); // Destructor
};
#endif