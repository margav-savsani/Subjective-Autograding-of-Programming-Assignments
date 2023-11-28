#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    comparisons = 0;
    tree = new BST();
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (finish == start)
        return true;
    Journey *p;
    if (choice == 1)
        p = choose_one(array, start, finish);
    else if (choice == 2)
        p = choose_two(array, start, finish);
    else if (choice == 3)
        p = choose_three(array, start, finish);
    // else if (choice == 4)
    //     p = choose_four(array, start, finish);
    Journey pivot(p->getJourneyCode(), p->getPrice());
    int left = start - 1, right = finish + 1;
    while (true)
    {
        do
        {
            right--;
            comparisons++;
        } while (pivot < array[right] && right > start);

        do
        {
            left++;
            comparisons++;
        } while (array[left] < pivot && left < finish);

        if (left < right)
        {
            Journey temp(array[left].getJourneyCode(), array[left].getPrice());
            array[left] = array[right];
            array[right] = temp;
        }
        else if (left == right)
        {
            if (left < finish)
                left++;
            if (right > start)
                right--;
            break;
        }
        else
            break;
    }

    Quicksort(start, right);
    Quicksort(left, finish);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if (finish == start)
        return true;
    Journey *p;
    if (choice == 1)
        p = choose_one(array, start, finish);
    else if (choice == 2)
        p = choose_two(array, start, finish);
    else if (choice == 3)
        p = choose_three(array, start, finish);
    // else if (choice == 4)
    //     p = choose_four(array, start, finish);
    Journey pivot(p->getJourneyCode(), p->getPrice());
    tree->insert(p->getJourneyCode(), p->getPrice());
    int left = start - 1, right = finish + 1;
    while (true)
    {
        do
        {
            right--;
            comparisons++;
        } while (pivot < array[right] && right > start);
        do
        {
            left++;
            comparisons++;
        } while (array[left] < pivot && left < finish);
        if (left < right)
        {
            Journey temp(array[left].getJourneyCode(), array[left].getPrice());
            array[left] = array[right];
            array[right] = temp;
        }
        else if (left == right)
        {
            if (left < finish)
                left++;
            if (right > start)
                right--;
            break;
        }
        else
            break;
    }

    QuicksortWithBSTInsert(start, right);
    QuicksortWithBSTInsert(left, finish);
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

int SorterTree::getComparisons()
{
    return comparisons;
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