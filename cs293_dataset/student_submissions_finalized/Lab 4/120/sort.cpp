#include "sort.h"
#include <iostream>
#include "journey.h"

// Code up the functions defined in sort.cpp

int SorterTree::Partition(Journey* array,int start,int finish){
    int i,j;
    i=start-1;
    j=finish+1;

    while(true){
        while(array[j]<=x){
            j=j-1;
        }
        while(array[i]>=x){
            i=i+1;
        }
        if(i<j){
            Journey c=array[i];
            array[i]=array[j];
            array[j]=c;
        }
        else{
            return j;
        }
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
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
