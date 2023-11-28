#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "tree.h"
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
  SorterTree(int choice, int l, Journey* jarray); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool Quicksort_k(int start, int finish, int k);
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  Journey* choose_pivot(Journey* x, int start, int finish);
  int get_comparisons();
  void array_init();
  ~SorterTree(); // Destructor
};

#endif