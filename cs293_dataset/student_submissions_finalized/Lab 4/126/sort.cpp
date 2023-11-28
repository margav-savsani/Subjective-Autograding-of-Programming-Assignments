#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice=choice;
    this->l=l;
    array=new Journey[l];
}

bool SorterTree::Quicksort(int start, int finish)
{
    if(start==finish){
        return true;
    }
    std::cout<<((start+finish)/2)<<std::endl;
    if(start<finish){
        int i=start-1;
        int j=finish+1;
        while(true){
            do{
                i=i+1;
            }while(array[int((start+finish)/2)] <= array[i]);

            do{
                j=j-1;
            }while(array[j] <= array[int((start+finish)/2)]);
            if(i<j){
                Journey temp;
                temp=array[j];
                array[j]=array[i];
                array[i]=temp;
            }
            else
                break;
        }                
            Quicksort(start, j);
            Quicksort(j+1, finish);
            return true;
    }
    return true;
}       
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting


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
