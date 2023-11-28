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
int swap(int start ,int finish) {
    Journey temp  =  array[i];
    array[i] = array[j];
    array[j] = temp;
}
 
 
int partition(int start, int finish)
{
    Journey pivot = array[finish];
    int i = l - 1;
    for (int j = l; j < finish; j++)
    {
        if (array[j] < pivot)
        {
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, finish);
    return i + 1;
}
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
