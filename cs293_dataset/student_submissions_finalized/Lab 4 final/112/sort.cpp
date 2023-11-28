#include "sort.h"
#include <cstdlib>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    srand((unsigned)time(NULL));
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    for (int i = 0; i < l; i++)
    {
        cin >> array[i].JourneyCode >> array[i].price;
    }
    tree = new BST(); // need to implement BSt
    comparisons = 0;
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
        Journey *pivot;
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
        }
        int middle = partition(pivot, start, finish);
        while (middle == start - 1 || middle == finish) // infinite recursion of quicksort. need to change the pivot
        {
            pivot = &array[start + (rand() % (finish - start + 1))];
            middle = partition(pivot, start, finish);
        }
        Quicksort(start, middle);
        Quicksort(middle + 1, finish);
        return true;
    }
}

// partition function in naveen garg sir slides
int SorterTree::partition(Journey *pivot, int start, int finish)
{
    int i = start, j = finish; // iterators starting from either end of the subarray
    while (true)
    {
        while (!(array[j] < *pivot) && (j >= start))
        {
            j--;
            comparisons++;
        }
        comparisons++;
        while ((array[i] < *pivot) && (i <= finish))
        {
            i++;
            comparisons++;
        }
        comparisons++;
        if (i > j)
        {
            return j;
        }
        else // i and j now need to be interchanged
        {
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start > finish)
    {
        return false;
    }
    else if (start == finish)
    {
        if (!array[start].isPrinted)
        {
            array[start].isPrinted = true;
            tree->insert(array[start].getJourneyCode(), array[start].getPrice());
        }
        return true;
    }
    else
    {
        Journey *pivot;
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
        }
        int middle = partition(pivot, start, finish);
        while (middle == start - 1 || middle == finish) // infinite recursion of quicksort. need to change the pivot
        {
            pivot = &array[start + (rand() % (finish - start + 1))]; // random pivot
            middle = partition(pivot, start, finish);
        }
        if (pivot->isPrinted == false) // to ensure each journey is printed only once
        {
            pivot->isPrinted = true;
            tree->insert(pivot->getJourneyCode(), pivot->getPrice());
        }
        QuicksortWithBSTInsert(start, middle);
        QuicksortWithBSTInsert(middle + 1, finish);
        if (start == 0 && finish == l - 1)
        {
            for (int i = 0; i < l; i++)
            {
                array[i].isPrinted = false;
            }
        }
        return true;
    }
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
}

void SorterTree::printTree()
{
    cout << endl;
    cout << "Comparisions: " << comparisons << endl;
    cout << "Imbalance of Tree: " << tree->getImbalance() << endl;
    cout << endl;
    tree->printBST("Hi");
}