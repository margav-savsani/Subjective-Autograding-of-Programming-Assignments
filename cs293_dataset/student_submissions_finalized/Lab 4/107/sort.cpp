#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
  this->choice=choice;
  this->l=l;
  array = new Journey[l];
}

void SorterTree::swap(int one, int two)
{
  Journey* temp= array[one];
  array[one]=array[two];
  array[two]=temp;
}

int SorterTree::partition(Journey* pivot, int start, int finish)
{
  int i= start;
  int j= finish;
  Journey* tocompare=new Journey(pivot->getJourneyCode, pivot->getPrice);
  while (true)
  {
    while(tocompare > array[j])
      j--;
    while(array[i] > tocompare)
      i--;
    if(i<j)
      swap(i, j);
    else
      return j;
  }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start < finish)
    {
      Journey* pivot;
      if(choice==1)
        pivot= choose_one(array, start, finish);
      else if(choice==2)
        pivot= choose_two(array, start, finish);
      else if(choice==3)
        pivot= choose_three(array, start, finish);
      else
        pivot= choose_four(array, start, finish);
      int pivot_val= partition(pivot, start, finish);
      Quicksort(start, pivot_val);
      Quicksort(pivot_val+1, end);
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}

bool insertPivot(int JourneyCode, int )
{

}

BST* SorterTree::getTree()
{
  return tree;
}

~SorterTree
{
  delete [] array;
  delete tree;
}
