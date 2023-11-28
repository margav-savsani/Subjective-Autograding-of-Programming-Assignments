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
  int next;
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  int partition(Journey* array,int start,int end, Journey* pivot);
  ~SorterTree(); // Destructor
  bool QuicksortWithBSTInsertCore(int start, int finish);
  bool insertJourney(Journey j){
    if(next==l)
      return false;
    array[next] = j;
    next++;
    return true;
  }
};
#endif