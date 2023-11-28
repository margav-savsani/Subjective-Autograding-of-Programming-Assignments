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
  SorterTree(int choice, int l){
    this->choice - choice;
    this->l = l;

    this->array = new Journey[l];

    int journeyCode, price;

    for(int i = 0; i < l; i++){
      cin >> journeyCode >> price;
      array[i] = Journey(journeyCode, price);
    }

  }; // Define valid constructor
  int partiton(int start, int finish); // this function is added for implementing Quicksort
  int pivotchoice(int start, int finish); // will be used for setting pivot
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(){
    return tree;
  }; // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor

  int retCom(){ return comparisons; }
};
