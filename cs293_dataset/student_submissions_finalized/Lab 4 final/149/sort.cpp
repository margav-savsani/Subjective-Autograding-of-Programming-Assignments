#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree::sort(Journey *array, int lower, int upper)
{
    int i = lower;
    for (int j = lower; j < upper; j++)
    {
        if (array[j] < array[upper])
        {
            swap(array[i], array[j]);
            i++;
            compares++;
        }
    }
    swap(array[i], array[upper]);
    return i;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (finish - start <= 0)
        return false;
    Journey *j = new Journey();
    if (choice == 1)
    {
        j = choose_one(array, start, finish);
    }
    else if (choice == 2)
    {
        j = choose_two(array, start, finish);
    }
    else if (choice == 3)
    {
        j = choose_three(array, start, finish);
    }
    int i;
    for (i = start; i < finish; i++)
    {
        if (j->getJourneyCode() == array[i].getJourneyCode())
            break;
    }
    swap(array[i], array[finish]);
    i = sort(array, start, finish);
    Quicksort(start, i - 1);
    Quicksort(i + 1, finish);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (finish - start < 0)
        return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey *j;
    if (choice == 1)
    {
        j = choose_one(array, start, finish);
    }
    else if (choice == 2)
    {
        j = choose_two(array, start, finish);
    }
    else if (choice == 3)
    {
        j = choose_three(array, start, finish);
    }
    int i;
    for (i = start; i < finish; i++)
    {
        if (j->getJourneyCode() == array[i].getJourneyCode())
            break;
    }
    tree->insert(array[i].getJourneyCode(), array[i].getPrice());
    swap(array[i], array[finish]);
    i = sort(array, start, finish);
    QuicksortWithBSTInsert(start, i - 1);
    QuicksortWithBSTInsert(i + 1, finish);
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    return true;
}
