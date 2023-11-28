#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey x = array[finish];
    int i = start - 1;
    int j =  finish + 1;
    while(true){
        while(array[j].price >= x){
            j--;
        }
        while(array[i].price <= x){
            i--;
        }
        if(i<j){
            Journey temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
    if(start<finish){
        Quicksort(start , j);
        Quicksort(j+1 , finish);
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
