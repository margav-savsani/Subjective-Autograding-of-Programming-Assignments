#include "sort.h"
#include <iostream>
#include <cassert>
//#include "choose.h"   //check this

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    assert(choice >= 1 && choice <= 4);    //1 <= choice <= 4;
    this->l = l;
    array = new Journey[l];
    tree = new BST;
    comparisons = 0;   //what about int* codes??
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start > finish){
        return false;
    }       
    return true;
}

int SorterTree::PartitionSort(int start, int finish){
    assert(start <= finish);
    Journey* pivot;
    if(choice == 1){pivot = choose_one(array, start, finish);}
    else if(choice == 2){pivot = choose_two(array, start, finish);}
    else if(choice == 3){pivot = choose_three(array, start, finish);}
    else if(choice == 4){pivot = choose_four(array, start, finish);}
    int i = start;
    int j = finish;
    while(true){
        while(!(*pivot < array[i])){i += 1; comparisons += 1;}
        while(!(array[j] < *pivot)){j -= 1; comparisons += 1;}
        if(i < j){
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }    
        else{
            return j;
        }
    }
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    return false;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl; //journey code gives error
        //std::cout<<"Journey code: "<<array[i].JourneyCode<<"\tJourney Price:"<<array[i].getPrice()<<std::endl; //journey code gives error
    }
    return false;
}
