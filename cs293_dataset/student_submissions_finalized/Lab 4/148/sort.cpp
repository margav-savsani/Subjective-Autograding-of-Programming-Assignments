#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey *pivot = choose_one(array, start, finish);
    int partition = Partition(array+start, array+finish, pivot);
    Quicksort(start, partition);
    Quicksort(partition+1, finish);

}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

int SorterTree::Partition(Journey* start, Journey* end, Journey * pivot){
    // Partition the region betweem start and end, at pivot
    Journey *i = start;
    Journey *j = end;

    while (true){
        while(j < pivot){
            j = j-1;
        }
        while(pivot < i){
            i=i+1;
        }
        if (i < j){
            Journey *a = j;
            *j = *i;
            *i = *a;
        }
        else{
            return j-array;
        }
    }


}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
