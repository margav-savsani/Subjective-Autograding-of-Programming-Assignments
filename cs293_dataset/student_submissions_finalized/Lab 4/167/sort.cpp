#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
   if (start<finish){ 
     k=partition(start,finish);    // Call appropriate pivot function based on choice
     SorterTree(start,k);
     SorterTree(k+1,finish);         // Split into 2 parts based on pivot choice
    }                             // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start<finish){             // Call appropriate pivot function based on choice
      k=partition(start,finish);   // Split into 2 parts based on pivot choice
      SorterTree(start,k);
      SorterTree(k+1,finish);           // Recursively keep sorting
     }                              // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
