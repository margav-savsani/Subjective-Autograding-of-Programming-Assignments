#include "sort.h"
#include "choose.h"
#include <iostream>
// #include "choose.h"

// Code up the functions defined in sort.cpp

bool SorterTree::Quicksort(int start, int finish) {
    // Call appropriate pivot function based on choice
    Journey* pivot=choose_one(array, start, finish);
    // Split into 2 parts based on pivot choice
    int i=-1,j=num_journeys;
    while(true){
        do j--; while(!(array[j] < *pivot));
        do i++; while(!(array[i] > *pivot));
        if(i<j){ 
            //swapping i and jth element
            Journey temp = array[i];
            array[i]=array[j];
            array[j]=temp;
        }
        else break;
    }
    // Recursively keep sorting
    //j is partition value
    Quicksort(start, j);
    Quicksort(j,finish);
}


bool SorterTree::insertJourney(int JC, int P){
    if(num_journeys==l){return false;}
    if(num_journeys>0) array[num_journeys]=Journey(JC,P);
    return true;
}

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    comparisons=0;
    array=new Journey[l];
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish) {
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
