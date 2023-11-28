#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice_, int l_){
    choice = choice_;
    l = l_;
    array = new Journey[l];
    elements = 0;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start < finish){
        int begin = start;
        int end = finish;
        struct Journey* pivot;
        if(choice == 1){
            pivot = choose_one(array, begin, end);
        }
        else if(choice == 2){
            pivot = choose_two(array, begin, end);
        }
        else if(choice == 3){
            pivot = choose_three(array, begin, end);
        }
        else if(choice == 4){
            pivot = choose_four(array, begin, end);
        }
        while(true){
            while(array[begin] < *pivot){
                start++;
            }
            while(*pivot < array[end]){
                end--;
            }
            if(!(begin >= end)){
                Journey temp = array[begin];
                array[begin] = array[end];
                array[end] = array[begin];
                begin++;
                end--;
            }
            else{
                return true;
                break;
            }
        }

        Quicksort(start, end);
        Quicksort(end+1,finish);
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
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
 bool SorterTree::insertPivot(int JourneyCode, int price){
    if(elements < l){
        struct Journey* temp = new Journey(JourneyCode, price);
        array[elements] = *temp;
        elements++;
        return true;
    }
    return false;
 }