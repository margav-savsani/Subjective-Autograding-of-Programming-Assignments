#include "sort.h"
#include <iostream>

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    this->comparisons=0;
    this->array = new Journey[l];
    this->tree = new BST();
}

SorterTree::~SorterTree(){
    delete[] array;
    delete tree;
}

BST* SorterTree::getTree(){
    return this->tree;
}



// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    if (start==finish) return true;
    if (start>finish) return false;
    
    Journey the_pivot;
    switch (choice) { // Call appropriate pivot function based on choice
        case 1: {
            the_pivot= *(choose_one(array, start, finish));
            break;
        }
        case 2: {
            the_pivot= *(choose_two(array, start, finish));
            break;
        }
        case 3: {
            the_pivot= *(choose_three(array, start, finish));
            break;
        }
        case 4:{
            the_pivot= *(choose_four(array, start, finish));
        }
    }
    
    // Split into 2 parts based on pivot choice
    int i=start,j=finish;
    while(i<j){
        //looking for indices to be swapped
        for(;!(the_pivot<array[i])&&(i<j);i++){}
        for(;the_pivot<array[j]&&(i<j);j--){}
        if (i<j){
            std::swap(array[i],array[j]);
        }
    }
    // Recursively keep sorting
    Quicksort(start, i);
    Quicksort(i+1 ,finish);
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    if (start==finish) return true;
    if (start>finish) return false;
    
    Journey the_pivot;
    switch (choice) { // Call appropriate pivot function based on choice
        case 1: {
            the_pivot= *(choose_one(array, start, finish));
            break;
        }
        case 2: {
            the_pivot= *(choose_two(array, start, finish));
            break;
        }
        case 3: {
            the_pivot= *(choose_three(array, start, finish));
            break;
        }
        case 4:{
            the_pivot= *(choose_four(array, start, finish));
        }
    }
    // Insert chosen pivot into the tree appropriately
    insertPivot(the_pivot.getJourneyCode(),the_pivot.getPrice());
    // Split into 2 parts based on pivot choice
    int i=start,j=finish;
    while(i<j){
        //looking for indices to be swapped
        for(;!(the_pivot<array[i])&&(i<j);i++){}
        for(;the_pivot<array[j]&&(i<j);j--){}
        if (i<j){
            std::swap(array[i],array[j]);
        }
    }
    // Recursively keep sorting
    Quicksort(start, i);
    Quicksort(i+1 ,finish);
    return true;
    
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }

    return true;
}

bool SorterTree::insertPivot(int JourneyCode, int price)
{
    return tree->insert(JourneyCode,price);
}