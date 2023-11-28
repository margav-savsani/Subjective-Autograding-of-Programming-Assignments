#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if (start == finish){
        return true;
    }
    if (start > finish) return false;

    int front = start;
    int end = finish;
    Journey* jpivot = choose_five(array, start, finish);
    while (front < end){
        if(array[start] < *jpivot){
            front++;
        } else if ((*jpivot).getJourneyCode() <= array[end].getJourneyCode()){

            end--;
        } else {
            Journey temp(array[front].getJourneyCode(), array[front].getPrice());

            array[start] = array[end];
            array[end] = temp;

            front++;
            end--;


        }
    }
        
    SorterTree::Quicksort(start, front-1);
    SorterTree::Quicksort(end, finish);

        
    

    

    
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
