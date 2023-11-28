#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey * partition;
    if(finish<start){ 
        if(choice == 1){
            partition=choose_one(array, start, finish);
        }
        else if(choice == 2){
            partition=choose_two(array, start, finish);
        }
        else if(choice == 3){
            partition=choose_three(array, start, finish);
        }
        else{
            partition=choose_four(array, start, finish);
        }
        Quicksort(start,partition->getJourneyCode());
        Quicksort(partition->getJourneyCode()+1,finish);
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
