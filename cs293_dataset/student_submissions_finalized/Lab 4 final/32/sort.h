#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
 public:  
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int counter; // Total number of comparisons performed
  

  SorterTree(int choice, int l)
  {
    this->choice = choice;
    this->l = l;
    counter = 0; 
    array = new Journey[l];
    tree = new BST;
  }; // Define valid constructor
  
  int partition(int start, int finish);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  //~SorterTree(); // Destructor
};
#endif
