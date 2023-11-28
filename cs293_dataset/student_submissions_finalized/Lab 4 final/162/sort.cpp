#include "sort.h"
#include <iostream>

void SwapJourneys(Journey *j1, Journey *j2)
{
    Journey temp = *j1;
    *j1 = *j2;
    *j2 = temp;
}
// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
    tree = new BST();
    comparisons = 0;
    max = new Journey(-2147483648, 100);
    min = new Journey(2147483647, 100);
}

void SorterTree::insert(Journey *arr)
{
    for (int i = 0; i < l; i++)
    {

        array[i] = arr[i];
        if (*max < array[i])
        {
            *max = array[i];
        }
        if (array[i] < *min)
        {
            *min = array[i];
        }
    }
}

int SorterTree::Partition(Journey *pivot, int start, int finish)
{
    // swap
    Journey pivotElement = *pivot;
    int i = start;
    int j = finish;
    while (true)
    {
        while (pivotElement < array[j])
        {
            j--;
            comparisons++;
        }
        while (array[i] < pivotElement)
        {
            i++;
            comparisons++;
        }

        if (i < j)
        {

            SwapJourneys(&array[i], &array[j]);
        }
        else
        {

            return j;
        }
    }
    return -1;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey *pivot;
    switch (this->choice)
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
    case 4:
        pivot = choose_four(array, start, finish);
        break;
    default:
        return false;
    }

    //If a bad pivot is generated we quit
    if (start > finish)
        return false;
    if (*max < *pivot || *pivot < *min)
        return false;
    
    //For checking if the pivot is in the array or not, and thne modifying the array accordingly
    bool checkPivot = false;
    for (int i = start; i <= finish; i++)
    {
        if (pivot->getJourneyCode() == array[i].getJourneyCode())
        {
            checkPivot = true;
            break;
        }
    }
    //does partition
    int mid = Partition(pivot, start, finish);

    if (checkPivot)
    {
        Quicksort(start, mid - 1);
        Quicksort(mid + 1, finish);
    }
    else
    {   
        Quicksort(start, mid);
        Quicksort(mid + 1, finish);
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

    Journey *pivot;
    switch (this->choice)
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
    case 4:
        pivot = choose_four(array, start, finish);
        break;
    default:
        return false;
    }

    if (start > finish)
        return false;
    if (*max < *pivot || *pivot < *min)
        return false;
    insertPivot(pivot->getJourneyCode(), pivot->getPrice());

    bool checkPivot = false;
    for (int i = start; i <= finish; i++)
    {
        if (pivot->getJourneyCode() == array[i].getJourneyCode())
        {
            checkPivot = true;
            break;
        }
    }
    int mid = Partition(pivot, start, finish);
    if (checkPivot)
    {
        QuicksortWithBSTInsert(start, mid - 1);
        QuicksortWithBSTInsert(mid + 1, finish);
    }
    else
    {   

        QuicksortWithBSTInsert(start, mid);
        QuicksortWithBSTInsert(mid + 1, finish);
    }
    return true;
}

bool SorterTree::printArray()
{

    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    return 0;
}

bool SorterTree::insertPivot(int JourneyCode, int price)
{
    return tree->insert(JourneyCode, price);
}

BST *SorterTree::getTree()
{
    return this->tree;
}