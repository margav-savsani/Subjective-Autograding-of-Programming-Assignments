#include "sort.h"
#include <iostream>
using namespace std;

// Code up the functions defined in sort.cpp

void Partition(Journey* a, int start, int finish){
    int b=a[finish];
    int i=start-1;
    int j=finish+1;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey temp = array[finish];
    array[finish]=array[choice];
    array[choice]=temp;
    Partition(array ,start,finish);
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
