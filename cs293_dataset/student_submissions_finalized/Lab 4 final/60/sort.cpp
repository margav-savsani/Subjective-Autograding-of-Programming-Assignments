#include "sort.h"
#include <iostream>
// Code up the functions defined in sort.cpp
void SorterTree::swap(int i, int j)
{
    Journey ptr = array[j];
    array[j] = array[i];
    array[i] = ptr;
}
int SorterTree::partition(int start, int finish)
{
    Journey * pivot;
    if(choice == 1) pivot = choose_one(array, start, finish);
    else if(choice == 2) pivot = choose_two(array, start, finish);
    else if(choice == 3) pivot = choose_three(array, start, finish);
    int i = start-1;
    for(int j = start; j < finish; j++)
    {
        if(array[j].getJourneyCode() < (*pivot).getJourneyCode())
        {
            i++;
            swap(i, j);
        }
        swap(i+1, finish);
    }
    return i+1; 
}
int SorterTree::partition2(int start, int finish)
{
    Journey * pivot;
    if(choice == 1) pivot = choose_one(array, start, finish);
    else if(choice == 2) pivot = choose_two(array, start, finish);
    else if(choice == 3) pivot = choose_three(array, start, finish);
    int i = start-1;
    for(int j = start; j < finish; j++)
    {
        if(array[j] < (*pivot))
        {
            comparisons++;
            i++;
            swap(i, j);
        }
        swap(i+1, finish);
    }
    tree->insert(array[i+1].getJourneyCode(), array[i+1].getPrice());
    return i+1; 
}
bool SorterTree::Quicksort(int start, int finish)
{
    if(start<finish)
    {
        int partitionIndex = partition(start, finish);
        SorterTree::Quicksort(start, partitionIndex-1);
        SorterTree::Quicksort(partitionIndex+1, finish); 
        return true;
    }
    return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if(start<finish)
    {
        int partitionIndex = SorterTree::partition2(start, finish);
        SorterTree::Quicksort(start, partitionIndex-1);
        SorterTree::Quicksort(partitionIndex+1, finish); 
        return true;
    }
    return false;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true; 
}

bool SorterTree::insertPivot(int JourneyCode, int price)
{
    if(m<l)
    {
        Journey ins(JourneyCode, price);
        array[m] = ins;
        m++;
        return true;
    }
    return false;
}

BST * SorterTree::getTree()
{
    return tree;
}
int SorterTree::getNumOfComp()
{
    return comparisons;
}