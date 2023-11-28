#include "sort.h"
#include <iostream>

bool pivotInarray = 1;

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l)
{ // Define valid constructor

    this->choice = choice;
    this->l = l;
    comparisons = 0;
    array = new Journey[l];
    int JourneyCode, price;
    for (int i = 0; i < l; i++)
    {
        std::cin >> JourneyCode >> price;
        array[i] = Journey(JourneyCode, price);
    }
    tree = new BST();
}

int SorterTree::partition(int low, int high, Journey *pivot)
{
    pivotInarray = 0;

    int i = low;  // i initialized to start
    int j = high; // j initialized to end
    while (true)
    {
        for (; array[i] < *pivot; i++)
        { // increment i till you find an element greater than pivot
            comparisons++;
        }
        for (; *pivot < array[j]; j--)
        { // decrement j till you find an element less than pivot
            comparisons++;
        }
        if (i < j)
        {                             // if i is on left side and j is on right side
            swap(array[i], array[j]); // swap
        }
        else if (i == j)
        {
            pivotInarray = 1;
            return j; // return index of point where partition has to be done
        }
        else
        {
            pivotInarray = 0;
            return j;
        }
    }
}

bool SorterTree::Quicksort(int start, int finish)
{ // Call appropriate pivot function based on choice
    Journey pivot;

    if (start >= finish)
        return true;
    else if (finish - start == 1)
    {
        if (array[finish] < array[start])
        {
            swap(array[finish], array[start]);
        }
        return true;
    }
   
    if (choice == 1)
    {
        pivot = *choose_one(array, start, finish);
    }

    else if (choice == 2)
    {
        pivot = *choose_two(array, start, finish);
    }
    else if (choice == 3)
    {
        pivot = *choose_three(array, start, finish);
        
    }
    //  else if (choice == 4)
    // {
    //     pivot = choose_four(array, start, finish);
    // }
    

    // Split into 2 parts based on pivot choice
    
        int i = start;  // i initialized to start
        int j = finish; // j initialized to end
        while (i<j)
        {
            for (; array[i] < pivot; i++)
            { // increment i till you find an element greater than pivot
                comparisons++;
            }
            for (; pivot < array[j]; j--)
            { // decrement j till you find an element less than pivot
                comparisons++;
            }
            
            if (i == j)
            {
                Quicksort(start, j - 1);
                Quicksort(j + 1, finish);
                return true;
                // return index of point where partition has to be done
            }
            else if(i>j)
            {
                Quicksort(start, i - 1);
                Quicksort(j + 1, finish);
                return true;
            }
            swap(array[i], array[j]);
        }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice

    Journey pivot;

    if (start > finish)
        return true;
    if(start == finish){
        insertPivot(array[start].getJourneyCode(), array[start].getPrice());
    }
    else if (finish - start == 1)
    {
        if (array[finish] < array[start])
        {
            swap(array[finish], array[start]);
        }
        insertPivot(array[start].getJourneyCode(), array[start].getPrice());
        insertPivot(array[finish].getJourneyCode(), array[finish].getPrice());
        return true;
    }
   
    if (choice == 1)
    {
        pivot = *choose_one(array, start, finish);
    }

    else if (choice == 2)
    {
        pivot = *choose_two(array, start, finish);
    }
    else if (choice == 3)
    {
        pivot = *choose_three(array, start, finish);
        
    }
    //  else if (choice == 4)
    // {
    //     pivot = choose_four(array, start, finish);
    // }
    

    // Split into 2 parts based on pivot choice

        insertPivot(pivot.getJourneyCode(), pivot.getPrice());

        int i = start;  // i initialized to start
        int j = finish; // j initialized to end
        while (i<j)
        {
            for (; array[i] < pivot; i++)
            { // increment i till you find an element greater than pivot
                comparisons++;
            }
            for (; pivot < array[j]; j--)
            { // decrement j till you find an element less than pivot
                comparisons++;
            }
            
            if (i == j)
            {

                QuicksortWithBSTInsert(start, j - 1);
                QuicksortWithBSTInsert(j + 1, finish);
                return true;
                // return index of point where partition has to be done
            }
            else if(i>j)
            {
                QuicksortWithBSTInsert(start, i - 1);
                QuicksortWithBSTInsert(j + 1, finish);
                return true;
            }
            swap(array[i], array[j]);
        }
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price)
{ // insert node corresponding to chosen pivot in BST

    tree->insert(JourneyCode, price);
    return true;
}
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    cout << comparisons << "\n";
}

BST *SorterTree::getTree()
{
    // returns pointer to the tree of pivots
    tree->printBST("");
    cout << tree->getImbalance() << "\n";
    return tree;
}