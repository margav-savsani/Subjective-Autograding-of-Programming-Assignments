#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:   
 
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons=0; // Total number of comparisons performed
  
public:
  Journey* array;
  SorterTree(int choice1, int l1){choice=choice1;l=l1;array = new Journey[l];tree=new BST;}
  int partition(int ,int,Journey*,int &,int &);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  int getcomp(){return comparisons;}
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
