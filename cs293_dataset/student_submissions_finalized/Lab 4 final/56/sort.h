#ifndef SORT_H
#define SORT_H


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
  int comparisons; // Total number of comparisons performed
  int curr_elts;
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool QuicksortInter(int start, int finish); // Sort the array according to the stored values
  bool Quicksort(int start, int finish);
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  void insertJourney(int JourneyCode, int price);
  int Partition(int start, int finish, Journey* pivot);
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  int getComparisons();
  ~SorterTree(); // Destructor
};
#endif