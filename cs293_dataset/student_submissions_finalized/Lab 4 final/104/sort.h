#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "tree.cpp"
#include "choose.cpp"

class SorterTree
{
private:   
  Journey* array;
  
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  BST* tree;
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  int partition(int start, int finish); // partition function for when pivot is present in array
  int newPartition(int start, int finish, Journey* pivot); // partition function for when pivot isn't part of array
  bool QuicksortWithBSTInsert(int start, int finish, TreeNode* &rt, TreeNode* prnt); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
  void printCost();
};

#endif