#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:   
  struct Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int cardinality;
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  void Quicksort(int start, int finish); // Sort the array according to the stored values
  void QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  struct Journey* getPivot(int start,int finish);
  bool insert(Journey entry); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  void printTree();
  void Imbalance();
  int getcomp();
  ~SorterTree(); // Destructor
};
struct Journey* SorterTree::getPivot(int start, int finish)
{
    if(choice==1){

        return choose_one(array,start,finish); 
    }
    if(choice==2){
        return choose_two(array,start,finish); 
    }
    if(choice==3){
        return choose_three(array,start,finish); 
    }
  \
    return NULL;
}
