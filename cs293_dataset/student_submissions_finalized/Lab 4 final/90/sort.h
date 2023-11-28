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
  int comparisons; // Total number of comparisons performed
  int counter; //to count number of pivots added into//
  bool onceQS = true; //To aid printing number of comparisons after QuickSort.
  bool onceQSBST = true;//To aid printing number of comparisons after QuickSortwithBSTInsert.
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  void setArray(Journey* array); //updates the variable array.
  int Partition(int start, int finish);//Partitions the array about a pivot chosen.
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray(); //prints array
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  bool printTree();
  ~SorterTree(){}; // Destructor 
};

#endif
