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
  // int* codes; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  BST* tree; // The tree which stores the 
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  int returnindex(int start,int end);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  int getindexofjourney(Journey* given){
      return (given - array); //To get the index of the given Journey
  }
  SorterTree(int choice, int l, Journey* journeys); 
  BST* getTree(); // returns pointer to the tree of pivots
  int comparisons_count();
  ~SorterTree(){}; // Destructor
};
