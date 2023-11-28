#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp



bool SorterTree::Quicksort(int start, int finish)
{
    Journey pivot;
    // Call appropriate pivot function based on choice
    switch(choice)
    {
    case 1:
        pivot = *choose_one(array, start, finish);
        break;
    
    case 2:
        pivot = *choose_two(array, start, finish);
        break;
    
    case 3:
        pivot = *choose_three(array, start, finish);
        break;
    
    case 4:
        pivot = *choose_four(array, start, finish);
        break;
    
    default:
        break;
    }
    // Split into 2 parts based on pivot choice
    if(l==1) return true;
    int sortstart=0, sortend=l-1;
    while(true){
        while(array[sortstart] < pivot){
            sortstart++;
        }
        while(!(array[sortend] < pivot)){
            sortend--;
        }
        if(sortstart < sortend){
            Journey temp = array[sortend];
            array[sortend] = array[sortstart];
            array[sortstart] = temp;
        }
        else break;
    }
    // Recursively keep sorting
    Quicksort(0,sortend);
    Quicksort(sortstart, l-1);
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
