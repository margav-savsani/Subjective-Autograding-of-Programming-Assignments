#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.cpp"

class SorterTree
{
private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  int i=0;
  
public:
  SorterTree(int choice, int l) {
    this->l=l;
    this->choice=choice;
    array=new Journey[l];
    tree=new BST();
    comparisons=0;
  } // Define valid constructor

  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  void printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  void insertjourney(int JourneyCode, int price);
  BST* getTree() {
    return tree;
  } // returns pointer to the tree of pivots
  int partition (Journey* arr, int low, int high ,Journey pivot);
  int get_comparisions() {
    return comparisons;
  }
  ~SorterTree(); // Destructor
};
