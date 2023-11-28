#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
void SorterTree::swap(int i, int j)
{
    Journey* ptr = &array[j];
    array[j] = array[i];
    array[i] = *ptr;
}
int SorterTree::partition(int start, int finish)
{
    int pivot = finish;
    int i = start-1;
    for(int j = start; j < finish; j++)
    {
        if(array[j].getPrice() < pivot)
        {
            i++;
            swap(i, j);
        }
        swap(i+1, finish);
    }
    return i+1; 
}
bool SorterTree::Quicksort(int start, int finish)
{
    if(start<finish)
    {
        int pi = partition(start, finish);
        SorterTree::Quicksort(start, pi-1);
        SorterTree::Quicksort(pi+1, finish); 
        return true;
    }
    return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    return false;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true; 
}
