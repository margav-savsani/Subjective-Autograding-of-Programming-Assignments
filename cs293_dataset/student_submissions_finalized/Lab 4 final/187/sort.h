#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:   
  Journey *array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  int part(Journey *A,int start,int finish);
  void insertarr(int i,int JourneyCode, int price);
  int comp();
  bool QuicksortWithBSTInsert(int start, int finish);
  Journey *insertarr();// May need extra parameters depending on implementation
  void printArray();
  bool insertPivot(int JourneyCode, int price);// insert node corresponding to chosen pivot in BST
void getTree(); // returns pointer to the tree of pivots
   ~SorterTree(){
    delete tree;
   };
};
#endif