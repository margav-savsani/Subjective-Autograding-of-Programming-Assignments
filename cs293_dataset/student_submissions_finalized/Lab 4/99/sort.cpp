#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
}

int SorterTree::Partition(int start, int finish)
{
    Journey * pivot;
    switch (choice)
    {
        case 1:
            pivot = choose_one(array, start, finish);
            break;
        case 2:
            pivot = choose_two(array, start, finish);
            break;
        case 3:
            pivot = choose_three(array, start, finish);
            break;
        case 4:
            pivot = choose_four(array, start, finish);
            break;
        default:
            pivot = start;
            break;
    }
    int count = 0, current_index;
    for (int j = start; j <= finish; j++)
    {
        if (array[j] < *pivot) count++;
        else if (array[j] == *pivot) current_index = j;
    }
    swap(array[count], array[current_index]);
    int p = start, q = finish;
    while (p < count && q > count)
    {
        while (array[p] < array[count])
        {
            p++;
        }
        while (array[q] > array[count])
        {
            q--;
        }
        if (p < count && q > count)
        {
            swap(array[p], array[q]);
            p++; q--;
        }
    }
    return count;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start > finish) return 0;
    int index = Partition(start, finish);
    Quicksort(start, index - 1);
    Quicksort(index + 1, finish);
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