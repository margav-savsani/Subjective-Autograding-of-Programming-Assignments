#include "sort.h"
#include <iostream>
using namespace std;
// Code up the functions defined in sort.cpp
SorterTree :: SorterTree(int choice,int l){
    array = new Journey[l];

    
}
bool SorterTree::Quicksort(int start, int finish)
{       
    if(start == finish ){return true;}
 
            if( choice == 1){
     Journey* pivot = choose_one( array, start, finish); 
    }
        if( choice == 2){
             Journey* pivot = choose_two(array,start, finish); 
    }
        if(choice == 3){
            Journey* pivot = choose_three(array,start,finish); 
    }
        if( choice == 4)
    {       Journey* pivot = choose_four(array,start,finish); }
        
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
