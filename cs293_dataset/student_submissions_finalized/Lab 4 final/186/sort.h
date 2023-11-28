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
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();      // Print all the data of array of Journeys
  Journey *getJourney();  // returns the array of Journeys
  int comparisonsDone();  // returns the number of comparisons
  void swapElements(Journey *elem1, Journey *elem2);  // swap two elements 
  void insertNewJourney(Journey journey, int index);  // insert new journey into the array
  bool insertPivot(unsigned int JourneyCode,unsigned int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};

#endif
