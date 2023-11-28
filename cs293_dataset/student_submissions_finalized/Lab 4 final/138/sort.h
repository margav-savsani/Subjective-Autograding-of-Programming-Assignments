#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

//the main class
class SorterTree
{
private:   
//private variables of the class
  Journey* array; //array containing the journeys
  BST* tree; // The BST to be constructed
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  void insert();// inserts the data from the file in the array
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();//prints the array
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  int part(int start, int finish); // partitions he array based on pivot element
  int random_part(int start, int finish); // decides the pivot element based on choose file
  void swap(Journey *a, Journey *b); //swaps two elements
  int get_comparisons(); // returns the value of the private variable comparisons
  BST* get_tree(); //returns the private variable of BST
  int random_part_with_insert(int start, int finish);// decides the pivot element and makes the BST
};
  // ~SorterTree(); // Destructor