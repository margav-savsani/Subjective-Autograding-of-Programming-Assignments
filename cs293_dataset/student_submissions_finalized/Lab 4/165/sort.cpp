#include "sort.h"
#include <iostream>
#include <bits/stdc++.h>
#include "choose.h"


// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){ // Define valid constructor

    this->choice = choice;
    this->l = l;
    comparisons = 0;
    array = new Journey[l];
    int JourneyCode,price;
    for(int i = 0;i<l;i++){
        std::cin>>JourneyCode>>price;
        array[i]=Journey(JourneyCode,price);
    }

}

int SorterTree::partition( int low, int high,Journey* pivot) 
{ 
    int x = pivot->getJourneyCode();

    int i = low-1;//i initialized to start
    for (int i = low; array->getJourneyCode() < x ; i++);//increment i till you find an element greater than pivot

    int j = high + 1;//j initialized to end
    for(int j = high; x < array->getJourneyCode() ;j--);//decrement j till you find an element less than pivot

    if(i<j){//if i is on left side and j is on right side
       swap(array[i],array[j]);//swap
    }
    else{
        return j;//return index of point where partition has to be done
    }
} 
  

bool SorterTree::Quicksort(int start, int finish,int choice)
{
    // Call appropriate pivot function based on choice
    Journey* pivot;
    
    if(choice == 1){
        pivot = choose_one(array, start, finish);
    }


    // Split into 2 parts based on pivot choice
    if(start<finish){
        int temp = partition(start,finish ,pivot );

        // Recursively keep sorting
        Quicksort(start,temp,choice);
        Quicksort(temp + 1, finish,choice);
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
