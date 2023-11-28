#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    int mid = (start + finish) / 2;
    for (int i = 0; i < mid; i++)
    {
        if (array[i].getJourneyCode() > array[mid].getJourneyCode())
        {
            Journey *temp = array[i];
            array[i] = array[finish - start - i];
            array[finish - i - start] = temp;
        }
        Quicksort(mid + 1, finish);
        Quicksort(0, mid);
    }
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
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}
