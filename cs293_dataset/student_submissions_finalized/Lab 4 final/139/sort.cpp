#include "sort.h"
#include <iostream>
using namespace std;

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
    tree = new BST();
    comparisons = 0;
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
    int i = start - 1, j = finish + 1;
    while (true)
    {
        while (true)
        {
            comparisons++;
            j--;
            if (array[j].getJourneyCode() <= pivot->getJourneyCode())
                break;
        }
        while (true)
        {
            comparisons++;
            i++;
            if (array[i].getJourneyCode() >= pivot->getJourneyCode())
                break;
        }
        if (i < j)
        {
            swap(array[i], array[j]);
        }
        else if (j == finish)
            return j - 1;
        else
            return j;
    }
}

int SorterTree::INSERT_PIVOT(Journey *array, int start, int finish)
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
    insertPivot(pivot->getJourneyCode(), pivot->getPrice());
    int i = start - 1, j = finish + 1;
    while (true)
    {
        while (true)
        {
            comparisons++;
            j--;
            if (array[j].getJourneyCode() <= pivot->getJourneyCode())
                break;
        }
        while (true)
        {
            comparisons++;
            i++;
            if (array[i].getJourneyCode() >= pivot->getJourneyCode())
                break;
        }
        if (i < j)
        {
            swap(array[i], array[j]);
        }
        else if (j == finish)
            return j - 1;
        else
            return j;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    if (start >= finish)
    {
        return true;
    }
    int x = Partition(array, start, finish);
    Quicksort(start, x);
    Quicksort(x + 1, finish);
}

BST *SorterTree::getTree()
{
    return tree;
}

int SorterTree::Comparisons()
{
    return comparisons;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start >= finish)
    {
        return true;
    }
    int x = INSERT_PIVOT(array, start, finish);
    QuicksortWithBSTInsert(start, x - 1);
    QuicksortWithBSTInsert(x + 1, finish);
}
bool SorterTree::insertPivot(int journeyCode, int price)
{
    Journey J(journeyCode, price);
    Pivots.push_back(J);
}
bool SorterTree::insert(int journeyCode, int price, int i)
{
    Journey J(journeyCode, price);
    array[i] = J;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}

void SorterTree::insertPivots()
{
    for (int i = 0; i < Pivots.size(); i++)
    {
        tree->insert(Pivots[i].getJourneyCode(), Pivots[i].getPrice());
    }
}

void SorterTree::printTree()
{
    insertPivots();
    tree->printBST("");
    cout << tree->getImbalance() << endl;
}
int SorterTree::Imbalance(){
    return tree->getImbalance();
}
SorterTree::~SorterTree()
{
    // delete (tree, array, &choice, &comparisons);
}