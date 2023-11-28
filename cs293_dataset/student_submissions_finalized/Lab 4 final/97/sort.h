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
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  
public:
  int comparisons; // Total number of comparisons performed
  BST* tree;
  SorterTree(int choice, int l); // Define valid constructor
  void addJourney(int code, int price, int idx);
  bool checkElem(Journey* x);
  int Partition(int start, int finish);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  void insElem();
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
