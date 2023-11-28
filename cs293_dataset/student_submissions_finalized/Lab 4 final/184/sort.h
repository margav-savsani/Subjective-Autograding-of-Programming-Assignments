#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "tree.cpp"

class SorterTree
{
private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  int ind;
  SorterTree(int a, int b); // Define valid constructor
  void insert(int jrny_code,int cost);//function to insert th e entries into the array. 
  int partition(int start, int finish); // to generate partition for the array neede to sorted.
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  void printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};

#endif