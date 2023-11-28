#include "sort.h"
#include <iostream>

using namespace std;

// Code up the functions defined in sort.cpp

bool SorterTree::addJourney(int i, int j, int p)
{
    if (i >= l || i < 0) return 0;
    if (!(array[i].getJourneyCode() == -1 && array[i].getPrice() == -1)) return 0;
    array[i].input(j, p);
    return 1;
}

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    tree = new BST();
    comparisons = 0;
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
        /*case 4:
            pivot = choose_four(array, start, finish);
            break;*/
        default:
            pivot = nullptr;
            break;
    }
    if (pivot == nullptr) return 0;
    int actual_index = start, current_index;
    bool found = 0;
    for (int j = start; j <= finish; j++)
    {
        if (array[j] < *pivot) {actual_index++; comparisons++;}
        else if (array[j].getJourneyCode() == (*pivot).getJourneyCode() && array[j].getPrice() == (*pivot).getPrice()) {current_index = j; found = 1;}
    }
    if (!found) return -1;
    swap(array[actual_index], array[current_index]);
    int p = start, q = finish;
    while (p < actual_index && q > actual_index)
    {
        while (array[p] < array[actual_index])
        {
            p++;
            comparisons++;
        }
        while (array[actual_index] < array[q])
        {
            q--;
            comparisons++;
        }
        if (p < actual_index && q > actual_index)
        {
            swap(array[p], array[q]);
            p++; q--;
        }
    }
    return actual_index;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    //cout << "Quicksort start\n";
    if (start > finish) return 0;
    int index = Partition(start, finish);
    if (index < 0) return 0;
    insertPivot(array[index].getJourneyCode(), array[index].getPrice());
    bool forleft = 1, forright = 1;
    if (start <= index - 1) forleft = Quicksort(start, index - 1);
    if (index + 1 <= finish) forright = Quicksort(index + 1, finish);
    if (forleft && forright) return 1;
    else return 0;
}

bool SorterTree::insertPivot(int JourneyCode, int price)
{
    tree->insert(JourneyCode, price);
    return 1;
}

bool SorterTree::callQuickSort(int start, int finish)
{
    bool sorted = Quicksort(start, finish);
    if (!sorted) return 0;
    printArray();
    cout << "Total cost of comparisons: " << comparisons << endl;
    return 1;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (start > finish) return 0;
    bool done = Quicksort(start, finish);
    if (!done) return 0;
    tree->printBST("", false);
    return 1;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        cout << "Journey code: " << array[i].getJourneyCode() << " \tJourney Price:" << array[i].getPrice() << endl;
    }
    return 1;
}

BST * SorterTree::getTree()
{
    return tree;
}