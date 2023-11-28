#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
//#include "tree.cpp"
#include "journey.cpp"

int NUM_ELEMENTS = 128;


class SorterTree
{
private:   
  Journey* array;
  //int* codes; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  // TODO BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l){
  	array = new Journey[l];
  	this->l = l;
  	comparisons = 0;
  	this->choice = choice; 
  	//TODO tree = new BST();
 
  }; // Define valid constructor
  
  int addJourney(int index, Journey journey);
  
  int Partition(int start, int finish, Journey* pivot);
  void Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  //TODO BST* getTree(); // returns pointer to the tree of pivots
  //~SorterTree(); // Destructor
};
