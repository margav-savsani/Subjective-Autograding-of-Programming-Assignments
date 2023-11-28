#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.cpp"

class SorterTree
{
private:
  Journey *array;
  BST *tree;
  int choice;             // Choice of pivot function to use
  int l;                  // Total number of entries
  int comparisons;        // Total number of comparisons performed
  vector<Journey> Pivots; // Array of pivots.

public:
  SorterTree(int choice, int l);                      // Define valid constructor
  bool Quicksort(int start, int finish);              // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();                                  // Prints the Journey array
  bool insertPivot(int JourneyCode, int price); // insert the pivot to the vector
  BST *getTree();                               // returns pointer to the tree of pivots
  ~SorterTree();                                // Destructor
  int Partition(Journey *array, int start, int finish); // partition function used in quicksort algorithm
  bool insert(int journeyCode, int price, int i); //inserts the element into the array at index i.
  void insertPivots(); //inserts all pivots into tree.
  int Comparisons(); // returns no.of comparisons performed
  int Imbalance(); // returns imbalance of the tree
  int INSERT_PIVOT(Journey *array, int start, int finish); // INSERTS the pivot in the vector by calling insert pivot function.
  void printTree(); // Prints the tree
};
