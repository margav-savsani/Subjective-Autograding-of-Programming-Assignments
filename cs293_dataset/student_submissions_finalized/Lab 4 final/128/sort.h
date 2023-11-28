#ifndef SORT_H
#define SORT_H


#include <stdlib.h>
#include "tree.cpp"
// #include "journey.cpp"

class SorterTree
{
private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  // Define valid constructor
  SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    //cout<<"tree"<<endl;
    tree = new BST();
    
    comparisons = 0;
    array = new Journey[l];
    //cout<<"assigning"<<endl;
    for(int i=0 ; i<l ; i++){
      int new_code,new_price;
      cin >> new_code >> new_price;
      array[i] = Journey(new_code, new_price);
    }
    //cout<<"exited loop"<<endl;
  } 

  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(){return tree;} // returns pointer to the tree of pivots
  int getComparisons(){return comparisons;}
  ~SorterTree(){} // Destructor
};

#endif