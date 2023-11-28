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
  BST* tree2;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons=0; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l){
  
  	array = new Journey[1000];
  	tree = new BST();
  	tree2 = new BST();
  	this-> choice = choice;
  	this->l = l;
  } // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  void print(){// prints tree1
  
  	tree->printBST("");
  }
  int compare(){// returns number of comparisions
  
  	return comparisons;
  }
  int longest(){// to know longest path in tree2
  
  	return tree->maxii();
  }
  int shortest(){// to know the longest path in tree2
  
  	return tree->minii();
  }
  
  ~SorterTree(); // Destructor
};

#endif
