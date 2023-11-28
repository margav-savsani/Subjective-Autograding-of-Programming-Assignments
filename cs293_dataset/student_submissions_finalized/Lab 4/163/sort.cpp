#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    comparisons = 0;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (finish - start == 1)
        return true;
    Journey *pivot;
    if (choice == 1)
        pivot = choose_one(array, start, finish);
    else if (choice == 1)
        pivot = choose_two(array, start, finish);
    else if (choice == 1)
        pivot = choose_three(array, start, finish);
    else if (choice == 1)
        pivot = choose_four(array, start, finish);
    SorterTree *left = new SorterTree(choice, finish - start - 1);
    SorterTree *right = new SorterTree(choice, finish - start - 1);
    int l = 0, r = 0;
    for (int i = start; i < finish; i++)
    {
        if (array[i] < *pivot)
            left->array[l++] = array[i];
        else
            right->array[r++] = array[i];
    }
    left->Quicksort(0, l);
    right->Quicksort(0, r);
    for (int i = 0; i < l; i++)
        array[i + start] = left->array[i];
    for (int i = 0; i < r; i++)
        array[start + l + i] = right->array[i];
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
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

void SorterTree::insertJourney(int JourneyCode, int price, int i)
{
    (array[i]) = Journey(JourneyCode, price);
}

bool insertPivot(int JourneyCode, int price)
{
    return true;
}

BST *SorterTree::getTree()
{
    return tree;
}