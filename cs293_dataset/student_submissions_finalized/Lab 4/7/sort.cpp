#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp


SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
}


bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if(this->choice == 1){
        array = choose_one(array, start, finish);
    }

    else if(this->choice == 2){
        array = choose_two(array, start, finish);
    }

    else if(this->choice == 3){
        array = choose_three(array, start, finish);
    }

    else if(this->choice == 4){
        array = choose_four(array, start, finish);
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
