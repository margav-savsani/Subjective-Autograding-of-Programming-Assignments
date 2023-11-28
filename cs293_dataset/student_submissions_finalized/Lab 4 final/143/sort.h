#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.cpp"


class SorterTree
{
private:   
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  int i = 0;
public:
  Journey* array; //elements are to be inserted in this array
  SorterTree(int Choice, int L);// Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  int compare(); //returns comparisons
  void print(); //prints BST
  bool insertPivot(int JourneyCode,int price); //used to insert pivot into the tree
  bool printArray();//prints the array elements
  int Imbalance(); //returns the imbalance pf the tree
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(){}; // Destructor
};
