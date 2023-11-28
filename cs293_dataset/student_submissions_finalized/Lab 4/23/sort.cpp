#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    array = new Journey[l];
    }

bool SorterTree::Quicksort(int start, int finish)
{   Journey *pivot;
    if ( choice == 1 ){
      choose_one(array,start,finish);}
    if ( choice == 2 ){
      choose_two(array,start,finish);}
    if ( choice == 3 ){
      choose_three(array,start,finish);}
    if ( choice == 4 ){
      choose_four(array,start,finish);}
    
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
