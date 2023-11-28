#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice,int l){
    this->choice = choice;
    this->l = l;
    array = new Journey[l];
}

int SorterTree::midvalue(Journey *array,int start,int finish){
    int i = start;
    int j = finish;
    Journey* pivot;
    if(choice == 1){
    pivot = choose_one(array,start,finish);
    }
    else if(choice == 2){
    pivot = choose_two(array,start,finish);    
    }
    else if(choice == 3){
    pivot = choose_three(array,start,finish);    
    }
    else if(choice == 4){
    pivot = choose_four(array,start,finish);    
    }
    while(i<j){
        while(array[i]<*pivot){
            i=i+1;
        }
        while(array[j]>=*pivot){
            j =j-1;
        }
        if(i<j){
            int jc = array[i].JourneyCode;
            int pr = array[i].price;
            array[i].JourneyCode = array[j].JourneyCode;
            array[i].price = array[j].price;
            array[j].JourneyCode = jc;
            array[j].price = pr;
        }
        else {
          return j;
        }
    }  
}
bool SorterTree::Quicksort(int start, int finish)
{
    if(start < finish){
        int mid = midvalue(array,start,finish);
        Quicksort(start,mid);
        Quicksort(mid+1,finish);
        return true;
    }
    else{
        return false;
    }
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
