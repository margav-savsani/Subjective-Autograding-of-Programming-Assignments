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
  int n; // Total number of entries
  int comparisons; // Total number of comparisons performed
  int i ;
public:
  SorterTree(int choice, int n); // Define valid constructor
  bool Quicksort(int l, int r); // Sort the array according to the stored values
  bool Quicksortcall(int l, int r);
  bool ManyQuickSort(int l, int r,int k );
  bool QuicksortWithBSTInsert(int l, int r); // May need extra parameters depending on implementation
  bool printArray();
  bool insert_element(int JourneyCode, int price ) {  
    if ( i >= n ) return false ; 
    array[i++] = Journey(JourneyCode, price) ; 
    return true ; 
  }
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree() { 
    return tree ;
  } // returns pointer to the tree of pivots
  // ~SorterTree(); // Destructor
};
#endif