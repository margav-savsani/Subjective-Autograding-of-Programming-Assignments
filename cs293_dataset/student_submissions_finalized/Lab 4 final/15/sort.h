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
  int* codes; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  int Partition(int start,int finish,int pivot_index); 
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  int getComparisons(){return comparisons;}
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  int getLength(){return l;}
  BST* getTree(); // returns pointer to the tree of pivots
  void printBST(){tree->printBST("");}
  int get_imbalance(){return tree->getImbalance();}
  ~SorterTree(); // Destructor
};
