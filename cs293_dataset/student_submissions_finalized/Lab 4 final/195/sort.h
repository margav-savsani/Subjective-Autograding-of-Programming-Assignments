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
 // Stores the values of the entries (this is for feeding to the blackbox to obtain a pivot value)
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  int sz=0;
  int t;
public:
  SorterTree(int choice, int l){
       this->choice=choice;
       this->l=l;
       array=new Journey[l];
       comparisons=0;
       t=0;
       tree= new BST();
     } // Define valid constructor
  void input(int p,int q){
      Journey a(p,q);
       array[sz]=a;
       sz=sz+1;
       return;
      }
  int Partition(Journey* s,int a,int b,Journey d);
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  BST* call(){
     return tree;
     }
  bool insertPivot(int JourneyCode, int price){
        return tree->insert(JourneyCode,price);
         }
          // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  // Destructor
};
