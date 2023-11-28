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
  int i;
public:
  int cost;
  
  SorterTree(int choice, int l){
    this->choice=choice;
    this->l = l;
    i=0;
    array = new Journey[l];
    cost = 0;
    tree = new BST();
  } // Define valid constructor
  
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  int Partition(int start,int finish,int &cost);
  void addarray(unsigned int JourneyCode,unsigned int price);
  int Partition2(int start,int finish,int &cost,Journey* x);
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  void printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  //~SorterTree(); // Destructor
  void printtree();
};
#endif