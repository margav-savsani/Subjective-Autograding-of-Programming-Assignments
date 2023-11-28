#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
bool SorterTree::Quicksort(int start, int finish)
{
    if (start < finish)
    {
        Journey *pivot;
        if (choice == 1)
        {
            pivot = choose_one(array, start, finish);
        }
        else if (choice == 2)
        {
            pivot = choose_two(array, start, finish);
        }
        else if (choice == 3)
        {
            pivot = choose_three(array, start, finish);
        }
        else
        {
            pivot = choose_four(array, start, finish);
        }
        Journey x = *pivot;
        int i = start;
        int j = finish;
        // partition
        while (true)
        {
            while (array[j] <= x)
            {
                j--;
            }
            while (!(array[i] < x))
            {
                i++;
            }
            if (i < j)
            {
                Journey temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
            else
            {
                break;
            }
        }
        Quicksort(start, j);
        Quicksort(j, finish);
        return true;
    }
    else return false;
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
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}
