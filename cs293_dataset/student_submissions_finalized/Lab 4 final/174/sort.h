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
  SorterTree(int choice, int l);                // Define valid constructor

  void Quicksort(int start, int finish); // Sort the array according to the stored values
  
  void QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  
  void printArray();
  
  int part(int start, int finish);
  
  int choices(int start, int finish);
  
  bool insertPivot(int JourneyCode, int price){ // insert node corresponding to chosen pivot in BST
    return (tree->insert(JourneyCode,price));
  }; 
  
  BST* getTree(){   // returns pointer to the tree of pivots
    return tree;
  }; 
  void input(int jc, int pr, int pos){
    array[pos].add_new(jc,pr);
  }

  int imbal(){
    return tree->getImbalance();
  }

  void print_tree(){
    tree->printBST("");
    return;
  }
  
  int num_compar(){
    return comparisons;
  }
  ~SorterTree() {
    delete tree;
  }; // Destructor
};
