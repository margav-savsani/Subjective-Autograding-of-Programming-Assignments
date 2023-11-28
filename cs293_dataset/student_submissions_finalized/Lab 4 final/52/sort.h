#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "tree.cpp"

class SorterTree
{
private:   
  Journey* array; // array of journeys
  int index;      // index of array
  BST* tree;  // BST
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
  
  bool insert(unsigned int jc, unsigned int p); //insert function for getting journeys input

  int partition(int start, int end, Journey* pivot);  // partition function for quicksort

  void printResults();  // prints BST, number of comparisions and imbalance
};

#endif
