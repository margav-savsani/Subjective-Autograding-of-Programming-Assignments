#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this -> choice = choice;
    this -> l = l;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start < finish){
        Journey* pivot;
        if(SorterTree.choice == 1) pivot = choose_one(SorterTree.array,start,finish);
        else if(SorterTree.choice == 2) pivot = choose_two(SorterTree.array,start,finish);
        else if(SorterTree.choice == 3) pivot = choose_three(SorterTree.array,start,finish);
        else (SorterTree.choice == 4) pivot = choose_four(SorterTree.array,start,finish);
        for(int i=0;i<SorterTree.l;i++){
            if(SorterTree.array[i]==pivot) break;
        }
        Quicksort(start,i);
        Quicksort(i+1,finish);
    }
    for(int i=0;i<size(SorterTree.array)-1;i++){
        if(SorterTree.array[i]>SorterTree.array[i+1])return false;
    }
    return true;
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
