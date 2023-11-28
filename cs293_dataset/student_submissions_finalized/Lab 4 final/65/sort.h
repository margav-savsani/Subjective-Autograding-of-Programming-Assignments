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
  int i;
  int l; // Total number of entries
  
public:
int comparisons;
BST* tree;
  SorterTree(int choice, int l); // Define valid constructor
  int partition(Journey* array, int start, int finish, int piv);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool Insertjour(int JourneyCode,int price);
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
#endif
