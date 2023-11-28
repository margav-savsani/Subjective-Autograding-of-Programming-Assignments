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
  int n; //number of array indexes filled
  
public:
  SorterTree(int l, int choice); // Define valid constructor
  bool Quicksort(int start, int finish, int n); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish,int n); // May need extra parameters depending on implementation
  void printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  void insert(int j,int p);
  int partition(int start,int finish);//partition function for QuickSort
  int partitionTree(int start,int finish);//partition function for QuickSortwithBSTInsert
  //~SorterTree(); // Destructor
};

#endif
  