#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree(int choice, int l){
 sorterTree.choice=choice;
 sorterTree.l=l;
}

bool SorterTree::Quicksort(int start, int finish)
{
    int h=(start+finish)/2;
    choose_one(array,start,finish);
    Quicksort(start,h);
    Quicksort(h+1,finish);

    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
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
}
