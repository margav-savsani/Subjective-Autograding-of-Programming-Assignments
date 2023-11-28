#include "sort.h"
#include "choose.h"   
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey *(*choose_pivot)(Journey *, int , int);
    int init_start = start;
    if(choice == 1) choose_pivot = choose_one;
    else if(choice == 2) choose_pivot = choose_two;
    else if(choice == 3) choose_pivot = choose_three;
    else if(choice == 4) choose_pivot = choose_four;
    Journey *pivot = choose_pivot(array, start, finish);
    Journey temp = *pivot;
    while(true){
        while(!(array[start] > temp)) start++;
        while(!(array[finish] > temp)) finish--;
        if(start < finish){
            Journey x = array[start];
            array[start] = array[finish];
            array[finish] = x;
        }
        else{
            break;
        }
    }
    Quicksort(init_start, start - 1);
    Quicksort(start, finish);
    return true;
}

void SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
