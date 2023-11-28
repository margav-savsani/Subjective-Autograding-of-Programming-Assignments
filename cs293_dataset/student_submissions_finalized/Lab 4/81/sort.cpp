#include "sort.h"
#include "choose.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree::Partition(int start, int finish)
{   
    // Call appropriate pivot function based on choice
    if(choice==1){
        journey* pivot = choose_one(array, start, finish); 
    }
    if(choice==2){
        journey* pivot = choose_two(array, start, finish); 
    }
    if(choice==3){
        journey* pivot = choose_three(array, start, finish); 
    }
    if(choice==4){
        journey* pivot = choose_four(array, start, finish); 
    }
    int i=start-1;
    int j=finish+1;
    while(true){
        while(array[j]<(*pivot)){j--;}
        while(array[i]<(*pivot)){i++;}
        if(i<j) {
            journey J;
            J=array[i]
            array[i]=array[j];
            array[j]=J;
        }
        else return j;}
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}
bool SorterTree::Quicksort(int start, int finish)
{
if (start<finish){
    int q;
    q=Partition(start,finish);
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
