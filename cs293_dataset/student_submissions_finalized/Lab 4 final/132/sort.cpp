#include "sort.h"
#include <iostream>
#include<stdlib.h>

#include "tree.cpp"
// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{   
if (start < finish)
    {
        int pi =SorterTree::partition( start, finish);
        SorterTree::Quicksort( start, pi - 1);
        SorterTree::Quicksort(pi + 1, finish);
         return true;
    }return false;
}   
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{   

    if(start < finish){
        int pi = SorterTree::partition(start,finish);
        tree->insert(array[pi].getJourneyCode(),array[pi].getPrice());
        SorterTree::Quicksort(start,pi-1);
        SorterTree::Quicksort(pi+1,finish);
                return true;

    }
    return false;


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
