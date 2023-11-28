#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    Journey *pivot = choose_one(array, start, finish);
    if (choice == 2)
    {
        Journey *pivot = choose_two(array, start, finish);
    }
    if (choice == 3)
    {
        Journey *pivot = choose_three(array, start, finish);
    }

    if (start < finish)
    {
        int piv = 0;
        int pi = 0;
        for (int i = start; i < finish + 1; i++)
        {
            comparisons++;
            if (array[i].getJourneyCode() < pivot->getJourneyCode())
            {
                piv++;
            }
            else if (array[i].getJourneyCode() == pivot->getJourneyCode())
            {
                pi = i;
            }
        }

        array[pi] = array[piv];
        array[piv] = Journey(pivot->getJourneyCode(), pivot->getPrice());

        Quicksort(start, pi - 1);
        Quicksort(pi + 1, finish);
    }

    return 1;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    BST tree;

    Journey *pivot = choose_one(array, start, finish);
    if (choice == 2)
    {
        Journey *pivot = choose_two(array, start, finish);
    }
    if (choice == 3)
    {
        Journey *pivot = choose_three(array, start, finish);
    }

    if (start < finish)
    {
        int pi = 0;
        int piv = 0;
        for (int i = start; i < finish + 1; i++)
        {
            if (array[i].getJourneyCode() < pivot->getJourneyCode())
            {
                pi++;
                comparisons++;
            }
            else if (array[i].getJourneyCode() == pivot->getJourneyCode())
            {
                pi = i;
            }
        }

        array[pi] = array[piv];
        array[piv] = Journey(pivot->getJourneyCode(), pivot->getPrice());
        tree.insert(pivot->getJourneyCode(), pivot->getPrice());
        Quicksort(start, pi - 1);
        Quicksort(pi + 1, finish);
    }

    return 1;
}

int i = 0;

bool SorterTree::insertPivot(int JourneyCode, int price)
{
    array[i++] = Journey(JourneyCode, price);
    return 1;
}

BST *SorterTree::getTree()
{
    return tree;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    return 1;
}
