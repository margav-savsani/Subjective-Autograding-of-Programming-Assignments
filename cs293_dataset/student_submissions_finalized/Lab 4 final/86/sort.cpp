#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    tree = new BST();
    this->choice = choice;
    this->l = l;
    comparisons = 0;
    array = new Journey[l];
}
SorterTree::~SorterTree() {}
int SorterTree::partition(int start, int finish)
{
    if (start > finish)
        return -1;
    Journey *pivot;
    if (choice == 1)
    {
        pivot = choose_one(array, start, finish);
    }
    else if (choice == 2)
    {
        pivot = choose_two(array, start, finish);
    }
    else
    {
        pivot = choose_three(array, start, finish);
    }
    Journey temp = *pivot;
    *pivot = array[finish];
    array[finish] = temp;
    int i = start;
    int j = finish;
    while (true)
    {
        while (temp < array[j])
        {
            j--;
            comparisons++;
        }
        comparisons++;
        while (array[i] < temp)
        {
            i++;
            comparisons++;
        }
        comparisons++;
        if (i < j)
        {
            Journey just = array[j];
            array[j] = array[i];
            array[i] = just;
        }
        else
            return j;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start >= finish)
        return false;
    else
    {
        int pivot = partition(start, finish);
        if (pivot >= finish)
        {
            Quicksort(start, pivot - 1);
            return true;
        }
        else
        {
            Quicksort(start, pivot);
            Quicksort(pivot + 1, finish);
            return true;
        }
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (start >= finish)
        return false;
    else
    {
        int pivot = partition(start, finish);
        if (pivot >= finish)
        {
            QuicksortWithBSTInsert(start, pivot - 1);
            if (start <= pivot && pivot <= finish)
            {
                Journey temp = array[pivot];
                insertPivot(temp.getJourneyCode(), temp.getPrice());
            }
            return true;
        }
        else
        {
            QuicksortWithBSTInsert(start, pivot);
            QuicksortWithBSTInsert(pivot + 1, finish);
            if (start <= pivot && pivot <= finish)
            {
                Journey temp = array[pivot];
                insertPivot(temp.getJourneyCode(), temp.getPrice());
            }
        }
        return true;
    }
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}

bool SorterTree::insertPivot(int JourneyCode, int price)
{
    return tree->insert(JourneyCode, price);
}

BST *SorterTree::getTree()
{
    return tree;
}

void SorterTree::ins_journey(int JourneyCode, int price, int posn)
{

    Journey node(JourneyCode, price);
    array[posn] = node;
    return;
}
void SorterTree::print()
{
    tree->printBST("", false);
    return;
}
int SorterTree::Imbalance()
{
    return tree->getImbalance();
}
void SorterTree::compare()
{
    cout << comparisons << endl;
}
