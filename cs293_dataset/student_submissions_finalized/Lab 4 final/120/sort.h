#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:
  Journey* array; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  BST* tree;
  BST* bst;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons;
  int n; // Total number of comparisons performed
public:
  SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    tree = new BST();
    array=new Journey[l];
    comparisons=0;
    n=0;
  } // Define valid constructor
  void input(Journey *array){
    this->array=array;
    return;
  }

  int Partition(Journey* array,int start,int finish);
  int Partition1(Journey* array,int start,int finish);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price){
    return tree->insert(JourneyCode,price);
  } // insert node corresponding to chosen pivot in BST
  BST *getTree(){
    return tree;
  } // returns pointer to the tree of pivots // Destructor
};
