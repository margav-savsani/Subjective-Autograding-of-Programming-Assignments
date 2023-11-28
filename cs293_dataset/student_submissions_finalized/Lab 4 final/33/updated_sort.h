#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "updated_tree.cpp"
#include "choose.cpp"

class SorterTree
{
  public:
// private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l){
    this->choice = choice ;
    this->l = l ;
    comparisons = 0 ;
    tree = new BST() ;
    array = new Journey[l];
  };                            // Define valid constructor
  void swap(Journey &p,Journey &q);
  void printComparisons();
  int Breaking(Journey *arr,unsigned int m,unsigned int n,Journey pivot);
  bool Quicksort(int start, int finish,Journey *arr); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish,Journey *arr); // May need extra parameters depending on implementation
  void printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(){}; // Destructor
};
#endif
