#include "sort.h"
#include <iostream> 

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l)
{
    tree = NULL;
    this->choice = choice;
    this->l = l;
    comparisons = 0;
    array = new Journey[l];
}
 
int SorterTree::partition(int start,int finish)
{
    Journey* temp;
    if(choice == 1) 
    {
        temp = choose_one( array, start,  finish); 
    }
    else if(choice == 2) 
    {
        temp = choose_two( array, start,  finish); 
    }
    else if(choice == 3) 
    {
        temp = choose_three( array, start,  finish); 
    }
    else  
    {
        temp = choose_four( array, start,  finish); 
    }
    unsigned int x = temp->getJourneyCode();
    int i = start-1; int j = finish+1;
    while(true)
    {
        
    }
}

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
