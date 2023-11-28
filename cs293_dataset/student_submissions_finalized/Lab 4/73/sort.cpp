#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp
int SorterTree::Partition(int start,int finish)
{
    Journey *node;
    if (choice==1)
        node=choose_one(array,start,finish);
    if (choice==2)
        node=choose_two(array,start,finish);
    if (choice==3)
        node=choose_three(array,start,finish);
    if (choice==4)
        node=choose_four(array,start,finish);
    int i=start-1;
    int j=finish+1;
    while(true)
    {
        while(array[j]<(*node))
            j--;
        while(array[i]<*node)
            i++;
        if (i<j)
        {
            Journey J;
            J=array[i];
            array[i]=array[j];
            array[j]=J;
        }
        else
            return j;
    }
}
bool SorterTree::Quicksort(int start, int finish)
{
    if (start<finish)
    int Q;
    Q=Partition(start,finish);
    Quicksort(start,Q);
    Quicksort(Q+1,finish);
    
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
