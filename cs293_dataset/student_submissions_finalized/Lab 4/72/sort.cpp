#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l){
    this->choice = choice;
    this->l = l;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(start > finish)return false;
    else if(start == finish)return true;
    else{
        Journey* Jy;
        if(choice == 1)Jy=choose_one(array,start,finish);
        else if(choice == 2)Jy=choose_two(array,start,finish);
        else if(choice == 3)Jy=choose_three(array,start,finish);
        else if(choice == 4)Jy=choose_four(array,start,finish);
        int i=start;
        int j=finish;
        int piv;
        while(true){
            while(array[j] >= *Jy){
                j--;
            }
            while(array[j] < Jy){
                i++;
            }
            if(i<j){
                Journey J=array[i];
                array[i]=array[l];
                array[j]=J;
            }
            else{
                piv=j;
                break;
            }
        }
        Quicksort(start,piv);
        Quicksort(piv,finish);
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
