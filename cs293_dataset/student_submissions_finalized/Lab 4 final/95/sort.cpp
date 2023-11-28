#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
//constructor for SorterTree
SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l = l;
    this->comparisons = 0;
    this->array = new Journey[l];
    this->tree = new BST();
}

//assign value to journey
void SorterTree::insert(Journey arr[])
{
    for (int i = 0; i < l; i++)
    {
        array[i] = arr[i];
    }
    return;
}  

//print comparisions
void SorterTree::print_comparsions()
{
    cout << comparisons << endl;
}

//print bst
void SorterTree::print_bst()
{
    tree->printBST("");
}
   

//insert node to tree
bool SorterTree::insertPivot(int JourneyCode, int price)
{
    tree->insert(JourneyCode, price);
    return true;
}


//partition function for quicksort
int SorterTree::partition(int start, int finish, int pivot_element)
{
    int x = pivot_element;
    int i = start;
    int j = finish;

    while (true)
    {
        while (array[j].getJourneyCode() > x)
        {
            comparisons++;
            j = j - 1;
        }
        while (array[i].getJourneyCode() < x)
        {
            i = i + 1;
            comparisons++;
        }
        if (i < j)
        {
            Journey a = array[i];
            array[i] = array[j];
            array[j] = a;
        }
        else
        {
            return j;
        }
    }
}


//quicksort implementation
bool SorterTree::Quicksort(int start, int finish)
{
    if (start <= finish)
    {
        Journey *pivot_element;
        if (choice == 1)
        {
            pivot_element = choose_one(array, start, finish);
        }
        else if (choice == 2)
        {

            pivot_element = choose_two(array, start, finish);
        }
        else
        {
            pivot_element = choose_three(array, start, finish);
        }

        int q = partition(start, finish, pivot_element->getJourneyCode());

        Quicksort(start, q - 1);

        Quicksort(q + 1, finish);
    }

    return true;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}
   

   //quicksort implementation with insert
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start < finish)
    {
        Journey *pivot_element;
        if (choice == 1)
        {
            pivot_element = choose_one(array, start, finish);
        }
        else if (choice == 2)
        {
            pivot_element = choose_two(array, start, finish);
        }
        else
        {
            pivot_element = choose_three(array, start, finish);
        }
        tree->insert(pivot_element->getJourneyCode(), pivot_element->getPrice());
        int q = partition(start, finish, pivot_element->getJourneyCode());
        QuicksortWithBSTInsert(start, q - 1);
        QuicksortWithBSTInsert(q + 1, finish);
    }
    else if (start == finish)
    {
        Journey *pivot_element;
        if (choice == 1)
        {
            pivot_element = choose_one(array, start, finish);
        }
        else if (choice == 2)
        {
            pivot_element = choose_two(array, start, finish);
        }
        else
        {
            pivot_element = choose_three(array, start, finish);
        }
        tree->insert(pivot_element->getJourneyCode(), pivot_element->getPrice());
    }
    return true;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}  


//print imbalance
int SorterTree::imbalance()
{
    return tree->getImbalance();
}

// print array
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }

    return true;
}

SorterTree::~SorterTree()
{
    delete[] array;
}