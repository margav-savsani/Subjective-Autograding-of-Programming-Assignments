#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "tree.h"
#include "choose.h"
#include <functional>
#include <iostream>
using namespace std;
class SorterTree
{
private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  std::function<Journey *(Journey *, int, int)> pivot_func; // Stores the function that we are going to use
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  // BST* getTree(); // returns pointer to the tree of pivots
  //~SorterTree(); // Destructor
  bool insert(int jc, int price, int pos);
  void initWithRandomVals();
  bool isSorted(int start, int end);
  void printTreeData(){
    tree->printBST("", false);
    cout << "The imbalance is " << tree->getImbalance() << endl;
  }

  int Partition(Journey* start, Journey* end, Journey * pivot);
};
#endif