#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:   
  
  Journey *pivot;  //pivot for quicksort
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries

public:

  int comparisons; // Total number of comparisons performed
  Journey* array;
  SorterTree(int choice, int l, Journey* J){ // Define valid constructor
    SorterTree::l = l;
    SorterTree::choice = choice;
    comparisons = 0;

    this->array =J;

  } // Define valid constructor

  void insertJ(int Journeycode, int price , int j){
    Journey J(Journeycode,price);
    array[j]=J;
  }

  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  //int partition(int start, int finish);  //partition the given array for quick sort
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
