#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"
class SorterTree
{
private:   
  Journey* array;
  int* codes; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  int num;
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  int partition(int start,int finish);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  bool printComparisons();  //to print number of comparitions
  bool makearray(int JourneyCode,int price);  //to add elements
  bool printtree(); //printing the tree
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
#endif