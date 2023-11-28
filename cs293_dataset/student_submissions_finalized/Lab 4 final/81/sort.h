#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  Journey* array;
  SorterTree(int choice, int l){tree=new BST();array=new Journey[l];this->choice=choice;this->l=l;comparisons=0;}; // Define valid constructor
  int Partition_insert(int start, int finish);
  int Partition(int start, int finish);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
  int getComparisions();
};
