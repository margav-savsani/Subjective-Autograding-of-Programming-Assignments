#include <iostream>
using namespace std;
#include<vector>
#include<cmath>
#include <string>
#include <vector>
#ifndef SORT_H 
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree 
{
private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l,Journey * array); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  int partition(Journey * A,int p , int r);
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  int get_comp();
  void get_tree();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  int partition_ins(Journey * A,int p , int r);
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
