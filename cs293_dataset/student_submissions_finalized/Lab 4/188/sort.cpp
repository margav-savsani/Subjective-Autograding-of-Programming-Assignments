#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->array = new Journey[l];
};

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(choice == 1){
        Journey* p_array = choose_one(array, start, finish);

    }
    else if(choice == 2){
        Journey* p_array = choose_two(array, start, finish);
    }
    else if(choice == 3){
        Journey* p_array = choose_three(array, start, finish);
    }
    else if(choice == 4){
        Journey*p_array = choose_four(array, start, finish);
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
 
