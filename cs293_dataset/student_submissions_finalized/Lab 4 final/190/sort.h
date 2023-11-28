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
  int n; // Total number of Journeys in array.
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  BST* tree;
  SorterTree(int choice, int l); // Define valid constructor
  int Partition(int start, int finish);
  int Partition_with_BST_insert(int start, int finish);
  void swap(int p, int q);
  void Quicksort(int start, int finish); // Sort the array according to the stored values
  void QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  void insertPair(int JourneyCode, int price);
  BST* getTree(); // returns pointer to the tree of pivots
};
