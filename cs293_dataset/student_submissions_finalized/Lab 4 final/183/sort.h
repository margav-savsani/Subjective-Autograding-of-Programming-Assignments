#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:   
  BST* tree=new BST();
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons=0; // Total number of comparisons performed
  
public:
  Journey* array;
  SorterTree(int choice, int l){this->choice=choice;this->l=l;
                                array=new Journey[l];
                                } // Define valid constructor
  int partition(int p,int q,Journey* a);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  void printComparisons();
  void printbst();
  void printimbalance();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
