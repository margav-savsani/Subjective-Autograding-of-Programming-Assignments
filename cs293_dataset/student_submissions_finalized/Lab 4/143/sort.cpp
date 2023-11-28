#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    Journey *pivot;
    if(choice==1){
        pivot = choose_one(array,start,finish); 
    }
    if(choice==2){
        pivot = choose_two(array,start,finish); 
    }
    if(choice==3){
        pivot = choose_three(array,start,finish); 
    }
    if(choice==1){
        pivot = choose_four(array,start,finish); 
    }
    int i = start;
    int j =finish;
    while(true){
        while(array[i]<pivot){
            i = i + 1;
        }
        while(array[j]->JourneyCode>pivot->JourneyCode){
            j = j - 1;
        }
        Journey x = array[i];
        array[i] = array[j];
        array[j] = x;
        if(i>=j){
           return array;
        }
    }
    QuickSort(i,j);
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
