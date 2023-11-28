#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.h"
//#include "journey.cpp"
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
  void setArray(Journey* a); //sets the array
  SorterTree(int ch, int len); // Define valid constructor
  int partition(int start,int finish); //Forms Partition
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray(); //Prints Array
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  int getcomparisons(); //returns comparisons
  ~SorterTree(); // Destructor
};
