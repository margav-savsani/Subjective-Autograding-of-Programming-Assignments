#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"
#include "journey.cpp"

class SorterTree
{
private:   
  Journey* array;
  BST* tree;
  int choice;
  int l;
  int comparisons;
  
public:
  SorterTree(int choice, int l);
  SorterTree(int choice, int l, Journey* arr);

  void randomizer(int start, int finish);

  int part(int start, int finish);
  bool Quicksort(int start, int finish);

  int modified_part(int start, int finish);
  bool QuicksortWithBSTInsert(int start, int finish);

  bool printArray();

  Journey* master_choose(int start, int finish);
  int index_from_pointer(Journey* ptr);

  int getComparisons() {return comparisons;}
  int getImbalance() {return tree -> getImbalance();}

  BST* getTree();
  void printTree();
  ~SorterTree();
};

void swap(Journey* a, Journey* b);

