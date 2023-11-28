#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "tree.cpp"
#include "choose.cpp"

class SorterTree
{
private:   
  Journey* array;Journey* array1;
  //int* codes; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l,Journey * ary){this->choice=choice;this->l=l;comparisons=0;tree=new BST(); array =ary;array1=ary;};
  int Partition_insert(int start, int finish,Journey pivot);
  int Partition(int start, int finish,Journey pivot);// Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  int getcomp(){return comparisons;}
  
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(){return tree;}; // returns pointer to the tree of pivots
  ~SorterTree(){}; // Destructor
};
#endif