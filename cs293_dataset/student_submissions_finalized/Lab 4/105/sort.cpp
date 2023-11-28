#include "sort.h"
#include <iostream>

SorterTree::Journey(){
    array=new Journey
}

int SorterTree::Partition(array[],int start,int finish){
     int pivot = choose_one(Journey* array , int start , int finish);
    int i = start -1 ;
    for( j= start ;j < finish ; j++){
        if( array[j]<pivot){
            i++;
            swap(array[i],array[j]);
        }
    }

    swap(array[(i+1)],array[finish]);
    return (i+1);
}

bool SorterTree::Quicksort(array[] ,int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start<finish){
        int q = Partition( array[], start,finish);
        Quicksort(array , start,q);
        Quicksort(array,(q+1),finish);
    }

}


// Code up the functions defined in sort.cpp

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
