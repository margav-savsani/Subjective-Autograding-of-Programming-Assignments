#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "journey.cpp"
#include "tree.cpp"
#include "updated_sort.h"


SorterTree::Quicksort(int start, int finish) {
    Journey* cur_pivot;
    if(choice==1) {
        cur_pivot=choose_one(Journey* x, start, finish)
    }
    if(choice==2) {
        cur_pivot=choose_two(Journey* x, start, finish)
    }
    if(choice==3) {
        cur_pivot=choose_three(Journey* x, start, finish)
    }
    if(choice==4) {
        cur_pivot=choose_four(Journey* x, start, finish)
    }


}

/*
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
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
*/