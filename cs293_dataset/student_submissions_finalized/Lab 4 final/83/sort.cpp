#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree::partiton(int start, int finish)
{
    int pivot = finish; // this will give the pivot of array
    int index = start;

    for (int i = start; i < finish; i++)
    {
        if (array[i] < array[pivot])
        {
            swap(array[i], array[index]);
            index++;
        }
    }
    swap(array[finish], array[index]);
    return index;
}
int SorterTree::pivotchoice(int start, int finish)
{
    int pivot = choice; // chossing pivot
    swap(array[pivot], array[finish]);
    return SorterTree::partiton(start, finish);
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start < finish)
    {
        int partiotion_index = SorterTree::partiton(start, finish);

        SorterTree::Quicksort(start, partiotion_index - 1);
        SorterTree::Quicksort(partiotion_index + 1, finish);
        return true;
    }
    return false;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (start < finish)
    {
        int partition_index = SorterTree::partiton(start, finish);
        int p_index_JC = array[partition_index].getJourneyCode();
        int p_index_pr = array[partition_index].getPrice();
        SorterTree::Quicksort(start, partition_index - 1);
        SorterTree::Quicksort(partition_index + 1, finish);
        tree->insert(p_index_JC, p_index_pr);
        return true;
    }
    return false;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    return true;
}
