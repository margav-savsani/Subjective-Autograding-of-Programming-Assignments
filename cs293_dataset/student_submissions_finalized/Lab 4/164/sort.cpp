#include "sort.h"
#include <iostream>
// Code up the functions defined in sort.cpp
int SorterTree::Partition(int start,int finish)
{
    Journey *jour =choose_one(array, start, finish);
    int i=start;
    int j=finish;
    while (true)
    {
        while (!(array[j]<*jour))
        {
            j=j-1;
        }
        while (*jour<array[i])
        {
            i=i+1;
        }

        if(i<j)
        {
            Journey l=array[i];
            array[i]=array[j];
            array[j]=l;
        }
        else return j;
    }    
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start<finish)
    {
        int p= Partition(start,finish);
        Quicksort(start,p);
        Quicksort(p+1,finish);
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