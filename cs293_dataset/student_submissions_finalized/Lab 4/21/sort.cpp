#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
}

bool SorterTree::Quicksort(int start, int finish)
{
    int i = start;
    int j = finish;
    Journey pivot = array[(start+finish)/2];
    
    while(j>=i){
        while(array[i] < pivot) i++;
        while(array[j] < pivot) j--;
        if( j>= i){
            Journey temp = array[j];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }

        if(start < j) Quicksort(start,j);
        if(finish > i) Quicksort(i,finish);
        
    return true;

    };
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
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

int main(){
    for(int i=0 ; i<5; i++){
        Journey* j;
        cin >> j[i];
    }
    SorterTree 
    
}
