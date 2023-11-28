#include "sort.h"
#include <iostream>
#include "choose.h"
// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    comparisons = 0;
}
int SorterTree::partition(Journey *array, int start, int end)
{
    Journey x = array[end];
    int a = start - 1;
    int b = end + 1;
    while (true)
    {
        while (array[--b] < x)
        {
            comparisons++;
            continue;
        }
        while (x < array[++a])
        {
            comparisons++;
            continue;
        }
        if (a < b)
        {
            Journey temp;
            temp = array[a];
            array[a] = array[b];
            array[b] = temp;
        }
        else
        {
            return b;
        }
    }
}
bool SorterTree::Quicksort(int start, int finish)
{
    if (start < finish)
    {
        Journey *p;
        if (choice == 1)
        {
            p = choose_one(array, start, finish);
        }
        else if (choice == 2)
        {
            p = choose_two(array, start, finish);
        }
        else if (choice == 3)
        {
            p = choose_three(array, start, finish);
        }
        else if (choice == 4)
        {
            p = choose_four(array, start, finish);
        }
        Journey *temp;
        *temp = *p;
        *p = array[finish];
        array[finish] = *temp;
        int q = partition(array, start, finish);
        Quicksort(start, q);
        Quicksort(q + 1, finish);
        return true;
    }

    else
    {
        return false;
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
