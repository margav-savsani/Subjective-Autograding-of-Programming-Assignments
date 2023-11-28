#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "tree.cpp"
#include "journey.h"

class SorterTree
{
private:   
  Journey* array;
  //int* codes; // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    comparisons=0;
    array=new Journey[l];
    tree=new BST();
  }; // Define valid constructor
  int noofcomparisons(){
    return comparisons;
  }
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  int partition(int start,Journey*j,int finish);
  void takeinput(string s);
  void printtree();
  void exchange(Journey*a,Journey*b);
};
#endif