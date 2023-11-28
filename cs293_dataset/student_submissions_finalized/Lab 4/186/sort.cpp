#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    array = new Journey[l];
    this->choice = choice;
    this->l = l;
    comparisons = 0;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start < finish){
        int pivot = partition(array, start, finish);
        //cout << start << " " << pivot << " " << finish << endl;
        Quicksort(start,pivot-1);
        Quicksort(pivot+1,finish);
        return true;
    }
    return false;
}

int SorterTree::partition(Journey *array, int start, int finish){
    Journey journey = array[finish];
    int i = start, j = finish;
    while(true){
        while(journey < array[j]) j = j - 1;
        while(array[i] < journey) i = i + 1;
        if(i < j) swap(array[i],array[j]);
        else return j;
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

Journey *SorterTree::getJourney(){
    return array;
}

void SorterTree::insertNewJourney(Journey journey, int index){
    array[index] = journey;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

SorterTree::~SorterTree(){}
