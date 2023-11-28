#include "sort.h"
#include <iostream>
#include "choose.h"

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice_, int l_){
    choice=choice_;
    l=l_;
    comparisons=0;
}
bool SorterTree::Quicksort(int start, int finish)
{   
    Journey* pivot=(choice==1)? choose_one(array, start,finish) : (choice==2)? choose_two(array, start,finish) :(choice==3)? choose_three(array, start,finish) :(choice==4)? choose_four(array, start,finish);
    int i=0,low=0,j=l-1,high=l-1;
    while(true){
        while((*pivot)<((array[j]))){
            j--;
            comparisons++;
        }
        while(((array[i]))<(*pivot)){
            i++;
            comparisons++;
        }
        if(i<j){
            Journey temp= array[i];
            array[i]=array[j];
            array[j]=temp;
        }
        else break;
    }
    Quicksort(low,j);
    Quicksort(i,high);
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
