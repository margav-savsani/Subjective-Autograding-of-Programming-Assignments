#include <cassert>
#include "sort.h"

#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    tree = new BST;
}
int SorterTree::partition(int start, int finish)
{
    int p = -1;
    Journey *x;
    if (choice == 1)
        x = choose_one(array, start, finish);
    if (choice == 2)
        x = choose_two(array, start, finish);
    if (choice == 3)
        x = choose_three(array, start, finish);
    for (int i = start; i <= finish; i++)
    {
        if (x == &array[i])
            p = i;
    }
    swap(array[finish], array[p]);
    assert(p >= start && p <= finish);

    int i = start - 1;
    for (int j = start; j <= finish - 1; j++)
    {
        comparisons++;
        if (array[j].getJourneyCode() <= array[finish].getJourneyCode())
        {
            i = i + 1;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[finish]);
    return i + 1;
}

bool SorterTree::Quicksort(int start, int finish)
{

    if (start < finish)
    {
        int q = partition(start, finish);
        Quicksort(start, q - 1);
        Quicksort(q + 1, finish);
        return true;
    }
    return true;

    // Split into 2 parts based on pivot choice
    // Recursively keep sorting\

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start < finish)
    {
        int q = partition(start, finish);
        tree->insert(array[q].getJourneyCode(), array[q].getPrice());
        QuicksortWithBSTInsert(start, q - 1);
        QuicksortWithBSTInsert(q + 1, finish);
        // cout<<"Imbalance is: "<< tree->getImbalance()<<endl;
        return true;
    }
    return true;
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    tree->printBST("");
    cout << "Imbalance is : "<<tree->getImbalance() << endl;
    cout<<"Number of comparisons made : "<< comparisons<<endl;
}

BST *SorterTree::getTree()
{
    return tree;
}

bool SorterTree::insertPivot(int JourneyCode, int price)
{
    return true;
}
