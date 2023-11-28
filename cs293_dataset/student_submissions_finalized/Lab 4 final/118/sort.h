#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "journey.h"
#include "choose.h"

class SorterTree
{
private:   
  Journey* array;
  BST* tree=new BST;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l,Journey* a) // Define valid constructor
  {
    this->choice=choice;
    this->l=l;
    array=a;
  }
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  int CountQuicksort(int start, int finish);
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  int CountQuicksortWithBSTInsert(int start, int finish);
  bool printArray();
  TreeNode* insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(){} // Destructor
};
