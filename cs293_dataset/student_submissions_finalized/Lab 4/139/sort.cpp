#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

// // TODO:
// Journey *choose_one(Journey *x, int start, int finish);
// Journey *choose_two(Journey *x, int start, int finish);
// Journey *choose_three(Journey *x, int start, int finish);
// Journey *choose_four(Journey *x, int start, int finish);

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
}

int SorterTree::Partition(Journey *array, int start, int finish)
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
    else if (choice == 4)
    {
        pivot = choose_four(array, start, finish);
    }
    Journey *p = pivot - array;
    int i = start - 1;
    int j = finish + 1;
    while (true)
    {
        while (array[j].getJourneyCode() <= p->getJourneyCode())
        {
            j--;
        }
        while (array[j].getJourneyCode() >= p->getJourneyCode())
        {
            i++;
        }
        if (i < j)
        {
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        else
            return j;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{

    if (start > finish)
    {
        return false;
    }
    else if (start == finish)
    {
        return true;
    }
    else
    {
        int x = Partition(this->array, start, finish);
        Quicksort(start, x);
        Quicksort(x + 1, finish);
    }
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
