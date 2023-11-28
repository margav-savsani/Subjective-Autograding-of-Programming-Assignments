#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    switch(choice){
        case 1:
            array = choose_one;
        case 2:
            array = choose_two;
        case 3:
            array = choose_three;
        case 4:
            array = choose_four;
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    int pivot
    if(start < finish){
        then 
    }
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
