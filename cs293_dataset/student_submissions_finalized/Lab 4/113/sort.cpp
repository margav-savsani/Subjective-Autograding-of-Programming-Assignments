#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
}

SorterTree::~SorterTree()
{
    delete[] tree;
    delete[] array;
}

void SorterTree::swap(int i, int j)
{
    Journey k = array[i];
    array[i] = array[j];
    array[j] = k;
    return;
}

bool SorterTree::Quicksort(int start, int finish)
{

    if (start < finish)
    {
        int j = Partition(start, finish);
        Quicksort(start, j);
        Quicksort(j + 1, finish);
    }

    return true;
}

int SorterTree::Partition(int start, int finish)
{
    Journey *next_pivot;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    switch (choice)
    {
    case 1:
        next_pivot = choose_one(array, start, finish);
        break;
    case 2:
        next_pivot = choose_two(array, start, finish);
        break;
    case 3:
        next_pivot = choose_three(array, start, finish);
        break;
    case 4:
        next_pivot = choose_four(array, start, finish);
        break;
    }

    int i = start - 1;
    int j = finish + 1;
    while (true)
    {
        do
        {
            i = i + 1;
        } while (array[i] < *next_pivot);
        do
        {
            j = j - 1;
        } while (*next_pivot < array[j]);

        if (j < i)
        {
            return j;
        }
        else
        {
            swap(i, j);
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
    return true;
}
