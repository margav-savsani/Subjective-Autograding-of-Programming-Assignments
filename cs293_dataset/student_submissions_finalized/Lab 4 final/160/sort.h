#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "tree.cpp"
#include "choose.cpp"


class SorterTree
{
private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons=0; // Total number of comparisons performed
public:
  SorterTree(int c, int li){choice=c;l=li; }// Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  int partition(Journey arr[], int low, int high);
  Journey* partition_r(Journey A[], int low, int high);
  bool QuicksortWithBSTInsert(int start, int finish,Journey arr[]); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(){return tree;}
  int comp(){return comparisons;} // returns pointer to the tree of pivots
  //~SorterTree(); // Destructor
};
#endif
