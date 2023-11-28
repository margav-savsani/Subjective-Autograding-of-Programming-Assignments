#include "updated_sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int b = finish;
    int a = Array[finish];
    while (strat == finish)
    {
        if (Array[start] < Array[b])
        {
            start ++;
            finish --;
            continue;
        }
        else if (Array[start] > Array[b])
        {
            Array[start] == Array[finish];
            start ++;
            finish --;
        }
        
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
