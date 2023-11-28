#ifndef SORT_H
#define SORT_H
#include"tree.h"
#include"journey.h"

#include <stdlib.h>

class SorterTree
{
private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons=0; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  int Partition(Journey* array, int p, int r, int flag); // Partitions the array according to the pivot 
  Journey* getArray(); // returns the pointer to the first journey element in the array
  ~SorterTree(); // Destructor
  int getComparisons();
  void setComparisons(int i);
};

#endif
