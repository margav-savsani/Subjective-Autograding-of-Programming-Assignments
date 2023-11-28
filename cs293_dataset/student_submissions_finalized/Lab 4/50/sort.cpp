#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    comparisons = 0;
    array = new Journey [l];
    tree = new BST;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start < finish){
        Journey *pivot;
        if(choice == 1){
            pivot = choose_one(array, start, finish);
        }
        else if(choice == 2){
            pivot = choose_two(array, start, finish);
        }
        else if(choice == 3){
            pivot = choose_three(array, start, finish);
        }
        else if(choice == 4){
            pivot = choose_four(array, start, finish);
        }
        Journey *second;
        int s[l-1];
        Journey temp;
        temp = *pivot;
        *pivot = array[l-1];
        array[l-1] = temp;
        pivot = &array[l-1];
        int j = 0;
        for(int i = 0; i < l; i++){
            if(array[i] < *pivot && j != 0){
                Journey temp;
                temp = *second;
                *second = array[i];
                array[i] = temp;
            }
            else if(*pivot < array[i]){
                s[j] = i;
                j++;
            }
        }
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
