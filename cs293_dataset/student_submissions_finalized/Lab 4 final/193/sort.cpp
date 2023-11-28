#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l, Journey *journeys)
{
    array = journeys; // assigning the array to the newly created array.
    this->l = l;
    this->choice = choice;
    tree = new BST;
    comparisons = 0;
}

int SorterTree::returnindex(int start, int end)
{
    // Function to return the index from where the partition is made.
    Journey x = array[end];
    int smaller = (start-1);    
    for (int j = start; j<= end-1;j++){
        if(!(x < array[j])){
            comparisons++;
            smaller++;
            swap(array[smaller], array[j]);
        }
    }
    swap(array[smaller+1],array[end]);
    return (smaller+1);
}

bool SorterTree::Quicksort(int start, int finish)
{
    if (start < finish)
    {
        int index;
        if (choice == 1)
        {
            index = getindexofjourney(choose_one(array, start, finish));
        }
        if (choice == 2)
        {
            index = getindexofjourney(choose_two(array, start, finish));
        }
        if (choice == 3)
        {
            index = getindexofjourney(choose_three(array, start, finish));
        }
        if (index > finish || index < start)
        {
            return false;
        }
        swap(array[index], array[finish]); // Exchanging the Array elements.
        int indexofpart = returnindex(start, finish);
        Quicksort(start, indexofpart-1);
        Quicksort(indexofpart+1, finish);
    }
    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price)
{
    tree->insert(JourneyCode, price);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start < finish)
    {
        int index;
        if (choice == 1)
        {
            index = getindexofjourney(choose_one(array, start, finish));
        }
        if (choice == 2)
        {
            index = getindexofjourney(choose_two(array, start, finish));
        }
        if (choice == 3)
        {
            index = getindexofjourney(choose_three(array, start, finish));
        }
        if (index > finish || index < start)
        {
            return false;
        }
        insertPivot(array[index].getJourneyCode(),array[index].getPrice());
        swap(array[index], array[finish]); // Exchanging the Array elements.
        int indexofpart = returnindex(start, finish);
        QuicksortWithBSTInsert(start, indexofpart-1);
        QuicksortWithBSTInsert(indexofpart+1, finish);
    }
    return true;
}
int SorterTree::comparisons_count(){
    return comparisons;
}
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout << "Journey code: " << array[i].getJourneyCode() << "\tJourney Price:" << array[i].getPrice() << std::endl;
    }
    return true;
}
BST *SorterTree::getTree()
{
    return tree;
}