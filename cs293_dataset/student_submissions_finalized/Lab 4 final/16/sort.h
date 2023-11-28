#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:
  Journey *array;
  BST *tree;
  int choice;      // Choice of pivot function to use
  int l;           // Total number of entries
  int comparisons; // Total number of comparisons performed

public:
  SorterTree(int choice, int l);                      // Define valid constructor
  bool Quicksort(int start, int finish);              // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST *getTree();                               // returns pointer to the tree of pivots
  // ~SorterTree();                                // Destructor

  // Self made function to read from a file and to store it in array
  void make_array(string filename);

  // Making partition function, randomized partition function on the lines of video lecture\
  by Naveen Garg
  int Partition(int start, int finish);
  int RandomizedPartition(int start, int finish);

  // Accessor functions
  int get_comparisons();
  BST *get_BST_Tree();

  // PART 2
  int RandomizedPartition_BST(int start, int finish);
};
