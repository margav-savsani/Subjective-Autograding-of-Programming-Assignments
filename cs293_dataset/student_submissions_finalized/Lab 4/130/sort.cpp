#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(finish >= start) return true;
    
    Journey* pivot = choose_one(array, start, finish);
    for(int i = start; i <= finish; ++i)
    {
        if(i < pivot - array && *pivot < array[i])
        {
            Journey temp = array[i];
            array[i] = *pivot;
            *pivot = temp;

            pivot = array + i;
        }
        if(i > pivot - array && array[i] < *pivot)
        {
            Journey temp = array[i];
            array[i] = *pivot;
            *pivot = temp;

            pivot = array + i;
        }
    }
    Quicksort(start, pivot);
    Quicksort(pivot, finish);
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
