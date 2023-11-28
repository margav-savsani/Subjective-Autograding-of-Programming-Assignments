#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{   
    if(choice == 1){
        Journey *pivot ;
        pivot = choose_one( array,start,finish ) ;
    }
    else if(choice == 2){
        Journey *pivot ;
        pivot = choose_two( array,start,finish ) ;
    }
    else if(choice == 3){
        Journey *pivot ;
        pivot = choose_three( array,start,finish ) ;
    }
    else if(choice == 4){
        Journey *pivot ;
        pivot = choose_four( array,start,finish ) ;
    }
    int i = start-1 ;
    int j = finish+1 ;
    

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
