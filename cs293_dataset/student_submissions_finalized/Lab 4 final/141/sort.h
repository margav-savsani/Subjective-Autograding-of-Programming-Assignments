#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "journey.cpp"
#include "choose.cpp"

class SorterTree
{
private:   
  Journey* array;
  // int* codes; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed

  //friend void Quicksort(Journey* A, int p, int r);
  // friend void insertintoTree(SorterTree sorter , Journey* array);
  
public:
  // SorterTree(int choice, int l); // Define valid constructor
  SorterTree(Journey* A, int l, int choice = 1);
  //bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish, bool setpivot=true); // May need extra parameters depending on implementation
  void printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  int Partition(int start, int end);
  void quickSort(int start, int end);
  int getComparisons(){return comparisons;}

  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
