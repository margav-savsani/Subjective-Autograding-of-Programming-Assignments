#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
//#include "tree.cpp"
//#include "journey.cpp"
#include "choose.h"
#include <fstream>

class SorterTree
{
private:   
  Journey* arr;
  //BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  //bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  void insertelem(int jc , int p,int i);
  //bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  //BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
