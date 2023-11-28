// #include "tree.h"
// #include "journey.h"
#include "choose.h"

#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree::partition(int start, int end){
    Journey pivot;
    switch(choice){
        case 1:
            pivot = *choose_one(array, start, end);
            break;
        case 2:
            pivot = *choose_two(array, start, end);
            break;
        case 3:
            pivot = *choose_three(array, start, end);
            break;
        case 4:
            pivot = *choose_four(array, start, end);
            break;
        default:
            pivot = *choose_one(array, start, end);
            break;
    }

    int i = start-1;
    int j = end+1;
    while(true){
        do{
            j = j-1;
        }while(array[j] < pivot);

        do{
            i = i+1;
        }while(pivot < array[i]);

        if(i<j){
            Journey temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        else{
            return j;
        }
    }
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if(start < finish){
        int i = SorterTree::partition(start, finish);
        Quicksort(start, i);
        Quicksort(i+1, finish);
    }

    return 1;
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

    return 1;
}

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    this->array = new Journey[l];
    this->index = 0;
}

bool SorterTree::insert(unsigned int journeyCode, unsigned int price){
    Journey* j = new Journey;
    
    array[index++] = *j;

    return 1;
}