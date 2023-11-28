#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include<string>
#include "tree.h"
#include "journey.h"
#include "choose.h"

class SorterTree
{
private:   
	Journey* array;
	BST* tree;
	int choice; // Choice of pivot function to use
	int l; // Total number of entries
	Journey* choosePivot(int start, int finish); // chooses according to choose and gives the pivot
	int divideArray(int start,int finish,Journey* pivot) ;// This divides the array to pivot and returns index such that all journeys to left of pivot are greater than pivot while others are less
	  
public:
  SorterTree(Journey* array, int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};

#endif
