#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    comparisons = 0;
    array = new Journey [l];
    int code, price;
    tree = new BST;
    for(int i = 0; i < l; i++){
        cin >> code >> price;
        array[i] = Journey(code, price);
    }
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
        Journey temp;
        temp = *pivot;
        *pivot = array[finish];
        array[finish] = temp;
        pivot = &array[finish];
        int j = start-1;
        for(int i = start; i < finish; i++){
            comparisons++;
            if(array[i] < *pivot){
                j++;
                Journey t;
                t = array[j];
                array[j] = array[i];
                array[i] = t;
            }
        }
        if(*pivot < array[j+1]){
            temp = array[j+1];
            array[j+1] = *pivot;
            *pivot = temp;
        }
        Quicksort(start, j);
        Quicksort(j+2, finish);
        return true;
    }
    else return false;
}


bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
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
        tree->insert(pivot->getJourneyCode(), pivot->getPrice());
        Journey temp;
        temp = *pivot;
        *pivot = array[finish];
        array[finish] = temp;
        pivot = &array[finish];
        int j = start - 1;
        for(int i = start; i < finish; i++){
            comparisons++;
            if(array[i] < *pivot){
                j++;
                Journey t;
                t = array[j];
                array[j] = array[i];
                array[i] = t;
            }
        }
        temp = array[j+1];
        array[j+1] = *pivot;
        *pivot = temp;
        QuicksortWithBSTInsert(start, j);
        QuicksortWithBSTInsert(j+2, finish);
        return true;
    }
    else return false;
}

SorterTree::~SorterTree(){
    delete[] array;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
