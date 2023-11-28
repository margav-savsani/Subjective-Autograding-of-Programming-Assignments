#include "sort.h"
#include <iostream>
#include<cassert>
using namespace std;

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    tree = nullptr;
    comparisons=0;
    array = new Journey[l];
}
SorterTree::~SorterTree(){
    delete[] array;
    delete[] tree;
}

Journey* SorterTree::choose_pivot(Journey* x, int start, int finish){
    switch(choice){
        case 1:
            return choose_one(x, start, finish);
        case 2:
            return choose_two(x, start, finish);
        case 3:
            return choose_three(x, start, finish);
        case 4:
            return choose_four(x, start, finish);    
    }
    return nullptr;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey pivot = *choose_pivot(array, start, finish);
    // assert(pivot != nullptr);
    int left = start;
    int right = finish;
    while(right>left){
        while(array[left] < pivot){
            left++;
        }
        while(pivot < array[right]){
            right--;
        }
        if(left < right){
            swap(array[left], array[right]);
            assert(array[left] < pivot);
            assert( pivot < array[right]);
        }
        else{
            break;
        }
    }
    Quicksort(start, right);
    Quicksort(right, finish);
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
