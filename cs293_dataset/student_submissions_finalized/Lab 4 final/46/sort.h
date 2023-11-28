#ifndef SORT_H
#define SORT_H
#endif

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
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  int partition(Journey* arr, int start, int finish); // helper function for partitioning in Quicksort.
  int partition_1(Journey* arr, int start, int finish); // helper function for partitioning in inserting the pivots in the BST.
  int rand_partition(Journey* arr, int start, int finish);
  int rand_partition_1(Journey* arr, int start, int finish);
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool printTree();
  int get_comparisions();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  Journey* getArray(); // returns array pointer.
  ~SorterTree(); // Destructor
};
