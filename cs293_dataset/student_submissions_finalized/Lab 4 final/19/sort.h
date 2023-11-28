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
  Journey* array1;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  SorterTree(int choice, int l, Journey* arr);
  int partition(int start, int finish);
  int partrand(int start, int finish);
  void sort(int start, int finish);
  int partrand_BST(int start, int finish);
  int partition_BST(int start, int finish);
  void sort_BST(int start, int finish);
  int getcomp(){
    return comparisons;
  }
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(){
    return tree;
  }// returns pointer to the tree of pivots
  ~SorterTree(){}; // Destructor
};
