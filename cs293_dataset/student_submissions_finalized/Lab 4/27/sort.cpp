#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
using namespace std;

int partition (Journey*array,int start,int finish){
    Journey* pivot=choose_one(array,start,finish);
    Journey temp=*pivot;
    *pivot= array[finish];
    array[finish]=temp;
    //    Partition
    int i=start,j=finish;
    while(true){
        while(array[i]<temp){
        i++;
        }
        while(temp<array[j]){
            j--;
        }
        if(j>i){
            Journey temp2;
            temp2=array[j];
            array[j]=array[i];
            array[i]=temp2;
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
    if(finish>=start){
        int q=partition(array,start,finish);
        Quicksort(start,q);
        Quicksort(q+1,finish);
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
