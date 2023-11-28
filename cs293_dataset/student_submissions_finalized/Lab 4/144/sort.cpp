#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
}

int SorterTree::Partition(int start, int finish, Journey* pivot){
int begin = start - 1;
int end = finish + 1;

while(true){
    begin++;
    while(array[begin] < *pivot) begin++;
    end--;
    while(!(array[end] < *pivot) && end >= begin) end--;
    if(end > begin){
        Journey temp = array[begin];
        array[begin] = array[end];
        array[end] = temp;
    }
    else return begin;
}
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    return false; //TODO
}

bool SorterTree::printArray()
{
    // for (int i = 0; i < l; i++)
    // {
    //     std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    // }

    return true;
}

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
    this->array = new Journey[l];
    for(int i = 0; i < l; i++){
        unsigned int code, price;
        std::cin >> code, price;
        array[i] = Journey(code, price);
    }
}
