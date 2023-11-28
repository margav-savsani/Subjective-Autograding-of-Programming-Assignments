#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
  // Constructor
  this->choice=choice;
  this->l=l;
  fill=0;
  comparisons=0;
  tree = new BST();
  array = new Journey[l];
}

void SorterTree::swap(Journey* one, Journey* two)
{
  // swaps the entry one and two
  unsigned int temp=one->getJourneyCode();
  one->setJourneyCode(two->getJourneyCode());
  two->setJourneyCode(temp);
  temp=one->getPrice();
  one->setPrice(two->getPrice());
  two->setPrice(temp);
}


bool SorterTree::Quicksort(int start, int finish)
{
  if(start > finish)  // no array to sort
    return true;
  Journey* pivot; // our pivot
  if(choice==1)
    pivot= choose_one(array, start, finish);
  else if(choice==2)
    pivot= choose_two(array, start, finish);
  else if(choice==3)
    pivot= choose_three(array, start, finish);
  else
    pivot= choose_four(array, start, finish);
  if (pivot==nullptr) // If returned pivot is nullptr, exit sorting
    return false;

  int i= start; // this index moves right
  int j= finish;  // this index moves left
  Journey* tocompare=new Journey(pivot->getJourneyCode(), pivot->getPrice());
  while (true)
  {
    while(*tocompare < array[j]) // find JourneyCode lower than pivot's JourneyCode
    {
      comparisons++;
      j--;
    }
    comparisons++;
    while(array[i] < *tocompare)  // find JourneyCode higher than pivot's JourneyCode
    {
      comparisons++;
      i++;
    }
    comparisons++;
    if(i<j)
      swap(&array[i], &array[j]); //  swap if permissible i.e. i<j
    else
      break; // array is partitioned
  }
  if(i==j)  // this implies our pivot is in array and is at index i/j
  {
    return (Quicksort(start, j-1) && Quicksort(j+1, finish));  // sort lesser partition and sort greater partition
  }
  else if((start==i) || (finish==j))
  {
    return false; // when the pivot couldn't partition array i.e it's JourneyCode was either larger or smaller than all elements' JourneyCode
  }
  else   // array is partitioned
  {
    return (Quicksort(start, j) && Quicksort(j+1, finish));  // sort lesser partition and sort greater partition
  }
  return true;  // sorting complete
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
  if(start > finish)  // no array to sort
    return true;
  Journey* pivot;  // our pivot
  if(choice==1)
    pivot= choose_one(array, start, finish);
  else if(choice==2)
    pivot= choose_two(array, start, finish);
  else if(choice==3)
    pivot= choose_three(array, start, finish);
  else
    pivot= choose_four(array, start, finish);
  if (pivot==nullptr)  // If returned pivot is nullptr, exit sorting
    return false;

  insertPivot(pivot->getJourneyCode(), pivot->getPrice());

  int i= start; // this index moves right
  int j= finish;  // this index moves left
  Journey* tocompare=new Journey(pivot->getJourneyCode(), pivot->getPrice());
  while (true)
  {
    while(*tocompare < array[j])// find JourneyCode lower than pivot's JourneyCode
    {
      comparisons++;
      j--;
    }
    comparisons++;
    while(array[i] < *tocompare)  // find JourneyCode higher than pivot's JourneyCode
    {
      comparisons++;
      i++;
    }
    comparisons++;
    if(i<j)
      swap(&array[i], &array[j]); //  swap if permissible i.e. i<j
    else
      break; // array is partitioned
  }
  if(i==j)  // this implies our pivot is in array and is at index i/j
  {
    return (QuicksortWithBSTInsert(start, j-1) && QuicksortWithBSTInsert(j+1, finish)) ;  // sort lesser partition and sort greater partition
  }
  else if((start==i) || (finish==j))
  {
    return false; // when the pivot couldn't partition array i.e it's JourneyCode was either larger or smaller than all elements' JourneyCode
  }
  else  // array is partitioned
  {
    return (QuicksortWithBSTInsert(start, j) &&  QuicksortWithBSTInsert(j+1, finish) );  // sort lesser partition and sort greater partition
  }
  return true;  // sorting complete
}

bool SorterTree::insertPivot(int jc, int pc)
{
  // inserts pivot into BST
  return (tree->insert(jc, pc));
}

bool SorterTree::printArray()
{
    // prints array
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

bool SorterTree::insertJourney(int JourneyCode, int price)
{
  if(fill==l) // if full
    return false;
  // change attributes
  array[fill].setJourneyCode(JourneyCode);
  array[fill].setPrice(price);
  fill++;
  return true;
}

BST* SorterTree::getTree()
{
  return tree;
}

int SorterTree::getComparisions()
{
  return comparisons;
}

SorterTree::~SorterTree()
{
  delete [] array;
  delete tree;
}
