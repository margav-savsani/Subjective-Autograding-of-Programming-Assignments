#include "sort.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp

int SorterTree::partition(int low, int high)
{
    int i = low;
    int j = high;
    Journey pivot = array[low];
    while (i < j)
    {
        while (array[i] < pivot)
            i++;
        while (pivot < array[j])
            j--;
        if (i < j)
            swap(array[i], array[j]);
    }
    swap(array[low], array[j]);
    return j;
}

bool SorterTree::Quicksort(int start, int finish)
{
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
    int i = start;
    int j = finish;
    Journey pivot = array[start];
    while (i < j)
    {
        while (array[i] < pivot)
            i++;
        while (pivot < array[j])
            j--;
        if (i < j)
            swap(array[i], array[j]);
    }
    swap(array[start], array[j]);
    return j;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}


  
bool SorterTree::Quicksort(int start, int finish)
{
// Call appropriate pivot function based on choice
// Split into 2 parts based on pivot choice
// Recursively keep sorting
if (start < finish)
    {
        int pivot = partition(start, finish);
        Quicksort(start, pivot - 1);
        Quicksort(pivot + 1, finish);
    }
return true;
}