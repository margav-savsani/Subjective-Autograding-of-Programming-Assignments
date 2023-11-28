#ifndef SORT_H
#define SORT_H

#include "tree.h"
#include "journey.h"
#include "choose.h"

class SorterTree {
  private:
    Journey* array;
    BST* tree;
   
    // choice of pivot function to use
    int choice;
    // returns pointer to pivot depending on choice
    int choosePivot(int start, int finish);

    // total number of entries
    int l;
    int comparisons; 
    // constructors
  public:
    SorterTree(int choice, int l);
    SorterTree(int choice, int l, Journey* templ);
    // destructor
    ~SorterTree();
   
    // print array
    void printArray();

    // sort array[start:finish+1] according to the stored values
    void QuickSort(int start, int finish);
    // sort array[start:finish+1] according to the stored values while simultaneously populating the tree (assuming the tree is empty)
    void QuickSortWithBSTInsert(int start, int finish);
    
    // returns pointer to the tree of pivots
    BST* getTree();

    // returns number of comparisons performed during sorting
    int getComparisons();
};

#endif
