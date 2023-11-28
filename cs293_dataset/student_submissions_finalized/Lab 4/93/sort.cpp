#include "sort.h"   
#include "choose.h"
#include <iostream>
#include <cassert>

#ifndef SORT_H
#define SORT_H
#endif

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // assert(start>=0&&finish<l);
    if(start>=finish)
        return true;
    Journey* pivot;
    int j1 = 0;
    switch (choice)
    {
    case 1:{
        pivot = choose_one(array, start, finish);
        break;
    }
    case 2:{
        pivot = choose_two(array, start, finish);
        break;
    }
    case 3:{
        pivot = choose_three(array, start, finish);
        break;
    }
    case 4:{
        pivot = choose_four(array, start, finish);
        break;
    }
    default:
        break;
    }
    int i = start;
    int j = finish;
    //partition
    while(true){
        while(array[i]<*pivot)
            i++;
        while(!(array[j]<*pivot))
            j--;
        if(i<j){
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        else{
            j1 = j;
            break;
        }
    }
    Quicksort(start, j1);
    Quicksort(j1+1, finish);
    return true;
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
