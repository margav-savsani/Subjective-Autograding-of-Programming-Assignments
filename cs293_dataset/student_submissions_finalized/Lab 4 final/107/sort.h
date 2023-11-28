#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int fill; // Total filled
  int comparisons; // Total number of comparisons performed

public:
  SorterTree(int choice, int l); // Define valid constructor
  void swap(Journey *one, Journey* two); // swaps one and two
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertJourney(int JourneyCode, int price); // insert Journey in array
  bool insertPivot(int JourneyCode, int price); // insert Journey in array
  BST* getTree(); // returns pointer to the tree of pivots
  int getComparisions(); // returns total number of comparisions
  ~SorterTree(); // Destructor
};
